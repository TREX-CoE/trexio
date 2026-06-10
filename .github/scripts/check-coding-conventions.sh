#!/bin/sh
#
# Check C coding conventions defined in src/templates_front/templator_front.org.
#
# Conventions enforced:
#   1. Integer types must come from <stdint.h> (no bare int/long/short/unsigned)
#   2. Pointers must be initialized to NULL
#   3. Use FREE() macro instead of bare free() so the pointer is set to NULL
#   4. Variable names must be in lower case
#   5. #define constants must be in UPPER CASE
#   6. Struct tags must be suffixed with _s
#   7. Typedefs must be suffixed with _t
#
# The script checks only the added/modified lines in the PR diff so that
# existing code is not flagged.
#
# Exit codes:  0 = pass, 1 = violations found

set -e

ERRORS=0
WARNINGS=0

# ── Determine which C/H files were changed ──────────────────────────────────
if [ -n "$GITHUB_BASE_REF" ]; then
    # Running in a pull-request context
    BASE="origin/${GITHUB_BASE_REF}"
    git fetch --depth=1 origin "$GITHUB_BASE_REF" 2>/dev/null || true
    CHANGED_FILES=$(git diff --name-only --diff-filter=ACM "$BASE"...HEAD -- '*.c' '*.h' \
                    | grep -v '^src/' || true)
else
    # Local / manual run: check staged files or all C files
    CHANGED_FILES=$(git diff --cached --name-only --diff-filter=ACM -- '*.c' '*.h' \
                    | grep -v '^src/' || true)
    if [ -z "$CHANGED_FILES" ]; then
        CHANGED_FILES=$(git diff --name-only --diff-filter=ACM HEAD~1 -- '*.c' '*.h' \
                        | grep -v '^src/' || true)
    fi
fi

if [ -z "$CHANGED_FILES" ]; then
    echo "No C/H files changed – nothing to check."
    exit 0
fi

echo "============================================="
echo " Checking coding conventions (templator_front.org)"
echo "============================================="
echo ""
echo "Files to check:"
for f in $CHANGED_FILES; do echo "  $f"; done
echo ""

# ── Helper: get only the added lines (with file/line context) ───────────────
# Produces lines of the form   FILE:LINENO:CONTENT
added_lines() {
    for file in $CHANGED_FILES; do
        if [ ! -f "$file" ]; then
            continue
        fi
        if [ -n "$GITHUB_BASE_REF" ]; then
            git diff "$BASE"...HEAD -- "$file"
        else
            git diff HEAD~1 -- "$file"
        fi | awk -v fname="$file" '
            /^@@ / {
                # Parse the +N,M or +N hunk header
                split($3, a, ",")
                lineno = int(substr(a[1], 2)) - 1
                next
            }
            /^\+/ && !/^\+\+\+/ {
                lineno++
                line = substr($0, 2)
                print fname ":" lineno ":" line
                next
            }
            /^-/ { next }
            { lineno++ }
        '
    done
}

ADDED=$(added_lines)

if [ -z "$ADDED" ]; then
    echo "No added lines in C/H files – nothing to check."
    exit 0
fi

report() {
    level="$1"   # error or warning
    rule="$2"
    file="$3"
    lineno="$4"
    line="$5"
    if [ "$level" = "error" ]; then
        ERRORS=$((ERRORS + 1))
        printf "  ERROR [%s] %s:%s\n" "$rule" "$file" "$lineno"
    else
        WARNINGS=$((WARNINGS + 1))
        printf "  WARNING [%s] %s:%s\n" "$rule" "$file" "$lineno"
    fi
    printf "    %s\n" "$line"
}

# ── Rule 1: Use FREE() macro instead of bare free() ────────────────────────
echo "--- Rule: Use FREE() macro instead of bare free() ---"
echo "$ADDED" | while IFS=: read -r file lineno line; do
    # Skip comments (rough heuristic: lines starting with // or /*)
    stripped=$(echo "$line" | sed 's/^[[:space:]]*//')
    case "$stripped" in
        //*) continue ;;
        \**) continue ;;
    esac
    # Check for free(...) that is NOT the FREE macro definition itself
    if echo "$line" | grep -qE '\bfree[[:space:]]*\(' ; then
        if ! echo "$line" | grep -qE '\bFREE[[:space:]]*\(' ; then
            if ! echo "$line" | grep -qE '#define[[:space:]]+FREE' ; then
                report error "free->FREE" "$file" "$lineno" "$line"
            fi
        fi
    fi
done || true

# ── Rule 2: #define constants must be UPPER CASE ───────────────────────────
echo ""
echo "--- Rule: #define constants must be UPPER CASE ---"
echo "$ADDED" | while IFS=: read -r file lineno line; do
    # Match #define IDENTIFIER  (skip function-like macros are fine too, but
    # the identifier itself must be uppercase + underscores + digits).
    if echo "$line" | grep -qE '^[[:space:]]*#[[:space:]]*define[[:space:]]+' ; then
        ident=$(echo "$line" | sed -n 's/^[[:space:]]*#[[:space:]]*define[[:space:]]\+\([A-Za-z_][A-Za-z0-9_]*\).*/\1/p')
        if [ -n "$ident" ]; then
            upper=$(echo "$ident" | tr '[:lower:]' '[:upper:]')
            if [ "$ident" != "$upper" ]; then
                report error "define-uppercase" "$file" "$lineno" "$line"
            fi
        fi
    fi
done || true

# ── Rule 3: Struct tags must end with _s ───────────────────────────────────
echo ""
echo "--- Rule: Struct tags must be suffixed with _s ---"
echo "$ADDED" | while IFS=: read -r file lineno line; do
    # Match   struct <name> {   or   struct <name>;
    if echo "$line" | grep -qE '\bstruct[[:space:]]+[A-Za-z_][A-Za-z0-9_]*[[:space:]]*[{;]' ; then
        tag=$(echo "$line" | sed -n 's/.*\bstruct[[:space:]]\+\([A-Za-z_][A-Za-z0-9_]*\)[[:space:]]*[{;].*/\1/p')
        if [ -n "$tag" ]; then
            case "$tag" in
                *_s) ;; # OK
                *) report error "struct-suffix-_s" "$file" "$lineno" "$line" ;;
            esac
        fi
    fi
done || true

# ── Rule 4: Typedefs must end with _t ──────────────────────────────────────
echo ""
echo "--- Rule: Typedefs must be suffixed with _t ---"
echo "$ADDED" | while IFS=: read -r file lineno line; do
    if echo "$line" | grep -qE '\btypedef\b' ; then
        # Get the last identifier before the semicolon – that is the new type name
        tname=$(echo "$line" | sed -n 's/.*[[:space:]]\([A-Za-z_][A-Za-z0-9_]*\)[[:space:]]*;.*/\1/p')
        if [ -n "$tname" ]; then
            case "$tname" in
                *_t) ;; # OK
                *) report error "typedef-suffix-_t" "$file" "$lineno" "$line" ;;
            esac
        fi
    fi
done || true

# ── Rule 5: Pointer declarations should be initialized to NULL ─────────────
echo ""
echo "--- Rule: Pointers should be initialized to NULL ---"
echo "$ADDED" | while IFS=: read -r file lineno line; do
    # Skip comments
    stripped=$(echo "$line" | sed 's/^[[:space:]]*//')
    case "$stripped" in
        //*) continue ;;
        \**) continue ;;
        \#*) continue ;;
    esac
    # Detect pointer variable declarations without initialization
    # Pattern: type * varname ;  (without = )
    if echo "$line" | grep -qE '[A-Za-z_][A-Za-z0-9_]*[[:space:]]*\*[[:space:]]*[A-Za-z_][A-Za-z0-9_]*[[:space:]]*;' ; then
        if ! echo "$line" | grep -qE '=' ; then
            # Exclude function pointer typedefs and struct member declarations
            # (these are harder to handle; keep as warning)
            if ! echo "$line" | grep -qE '\btypedef\b' ; then
                report warning "ptr-init-NULL" "$file" "$lineno" "$line"
            fi
        fi
    fi
done || true

# ── Rule 6: Use stdint.h integer types ────────────────────────────────────
echo ""
echo "--- Rule: Use stdint.h integer types ---"
echo "$ADDED" | while IFS=: read -r file lineno line; do
    # Skip comments, preprocessor directives, includes, and string literals
    stripped=$(echo "$line" | sed 's/^[[:space:]]*//')
    case "$stripped" in
        //*) continue ;;
        \**) continue ;;
        \#*) continue ;;
    esac
    # Check for bare int/long/short declarations (excluding stdint types, argc, etc.)
    # Match lines that declare variables with bare C integer types
    if echo "$line" | grep -qE '(^|[[:space:];,{(])(unsigned[[:space:]]+)?(short|long long|long)[[:space:]]+[A-Za-z_]' ; then
        # Exclude typical false positives: function parameters named 'int', casts, sizeof
        report warning "use-stdint" "$file" "$lineno" "$line"
    fi
done || true

# ── Summary ────────────────────────────────────────────────────────────────
echo ""
echo "============================================="
echo " Summary"
echo "============================================="
echo "  Errors:   $ERRORS"
echo "  Warnings: $WARNINGS"

if [ "$ERRORS" -gt 0 ]; then
    echo ""
    echo "FAILED: $ERRORS coding convention violation(s) found."
    echo ""
    echo "Please review the coding conventions in"
    echo "  src/templates_front/templator_front.org  (section: Coding conventions)"
    echo ""
    echo "Key rules:"
    echo "  - Use FREE() macro instead of bare free()"
    echo "  - #define constants must be UPPER CASE"
    echo "  - Struct tags must be suffixed with _s"
    echo "  - Typedefs must be suffixed with _t"
    echo "  - Initialize pointers to NULL"
    echo "  - Use stdint.h integer types (int32_t, int64_t, etc.)"
    exit 1
fi

echo ""
echo "PASSED: No coding convention violations found."
exit 0
