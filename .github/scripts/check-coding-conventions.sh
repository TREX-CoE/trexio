#!/bin/sh
#
# Check C coding conventions defined in src/templates_front/templator_front.org.
#
# Conventions enforced:
#   1. Use FREE() macro instead of bare free() so the pointer is set to NULL
#   2. #define constants must be in UPPER CASE
#   3. Struct tags must be suffixed with _s
#   4. Typedefs must be suffixed with _t
#   5. Pointers should be initialized to NULL (warning)
#   6. Use stdint.h integer types (warning)
#
# The script checks only the added/modified lines in the PR diff so that
# existing code is not flagged.
#
# Exit codes:  0 = pass, 1 = violations found

set -e

ERRORS=0
WARNINGS=0
ADDED_FILE=$(mktemp)
trap 'rm -f "$ADDED_FILE"' EXIT

# ── Determine which C/H files were changed ──────────────────────────────────
if [ -n "$GITHUB_BASE_REF" ]; then
    BASE="origin/${GITHUB_BASE_REF}"
    git fetch --depth=1 origin "$GITHUB_BASE_REF" 2>/dev/null || true
    CHANGED_FILES=$(git diff --name-only --diff-filter=ACM "$BASE"...HEAD -- '*.c' '*.h' \
                    | grep -v '^src/' || true)
else
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

# ── Collect added lines into a temp file ────────────────────────────────────
# Format: FILE:LINENO:CONTENT
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
done > "$ADDED_FILE"

if [ ! -s "$ADDED_FILE" ]; then
    echo "No added lines in C/H files – nothing to check."
    exit 0
fi

# ── Rule 1: Use FREE() macro instead of bare free() ────────────────────────
echo "--- Rule: Use FREE() macro instead of bare free() ---"
while IFS=: read -r file lineno line; do
    stripped=$(echo "$line" | sed 's/^[[:space:]]*//')
    case "$stripped" in
        //*) continue ;;
        \**) continue ;;
    esac
    if echo "$line" | grep -qE '\bfree[[:space:]]*\(' ; then
        if ! echo "$line" | grep -qE '\bFREE[[:space:]]*\(' ; then
            if ! echo "$line" | grep -qE '#define[[:space:]]+FREE' ; then
                ERRORS=$((ERRORS + 1))
                printf "  ERROR [free->FREE] %s:%s\n" "$file" "$lineno"
                printf "    %s\n" "$line"
            fi
        fi
    fi
done < "$ADDED_FILE"

# ── Rule 2: #define constants must be UPPER CASE ───────────────────────────
echo ""
echo "--- Rule: #define constants must be UPPER CASE ---"
while IFS=: read -r file lineno line; do
    if echo "$line" | grep -qE '^[[:space:]]*#[[:space:]]*define[[:space:]]+' ; then
        ident=$(echo "$line" | sed -n 's/^[[:space:]]*#[[:space:]]*define[[:space:]]*\([A-Za-z_][A-Za-z0-9_]*\).*/\1/p')
        if [ -n "$ident" ]; then
            upper=$(echo "$ident" | tr '[:lower:]' '[:upper:]')
            if [ "$ident" != "$upper" ]; then
                ERRORS=$((ERRORS + 1))
                printf "  ERROR [define-uppercase] %s:%s\n" "$file" "$lineno"
                printf "    %s\n" "$line"
            fi
        fi
    fi
done < "$ADDED_FILE"

# ── Rule 3: Struct tags must end with _s ───────────────────────────────────
echo ""
echo "--- Rule: Struct tags must be suffixed with _s ---"
while IFS=: read -r file lineno line; do
    if echo "$line" | grep -qE '\bstruct[[:space:]]+[A-Za-z_][A-Za-z0-9_]*[[:space:]]*[{;]' ; then
        tag=$(echo "$line" | sed -n 's/.*\bstruct[[:space:]]*\([A-Za-z_][A-Za-z0-9_]*\)[[:space:]]*[{;].*/\1/p')
        if [ -n "$tag" ]; then
            case "$tag" in
                *_s) ;;
                *) ERRORS=$((ERRORS + 1))
                   printf "  ERROR [struct-suffix-_s] %s:%s\n" "$file" "$lineno"
                   printf "    %s\n" "$line"
                   ;;
            esac
        fi
    fi
done < "$ADDED_FILE"

# ── Rule 4: Typedefs must end with _t ──────────────────────────────────────
echo ""
echo "--- Rule: Typedefs must be suffixed with _t ---"
while IFS=: read -r file lineno line; do
    if echo "$line" | grep -qE '\btypedef\b' ; then
        tname=$(echo "$line" | sed -n 's/.*[[:space:]]\([A-Za-z_][A-Za-z0-9_]*\)[[:space:]]*;.*/\1/p')
        if [ -n "$tname" ]; then
            case "$tname" in
                *_t) ;;
                *) ERRORS=$((ERRORS + 1))
                   printf "  ERROR [typedef-suffix-_t] %s:%s\n" "$file" "$lineno"
                   printf "    %s\n" "$line"
                   ;;
            esac
        fi
    fi
done < "$ADDED_FILE"

# ── Rule 5: Pointer declarations should be initialized to NULL ─────────────
echo ""
echo "--- Rule: Pointers should be initialized to NULL ---"
while IFS=: read -r file lineno line; do
    stripped=$(echo "$line" | sed 's/^[[:space:]]*//')
    case "$stripped" in
        //*) continue ;;
        \**) continue ;;
        \#*) continue ;;
    esac
    if echo "$line" | grep -qE '[A-Za-z_][A-Za-z0-9_]*[[:space:]]*\*[[:space:]]*[A-Za-z_][A-Za-z0-9_]*[[:space:]]*;' ; then
        if ! echo "$line" | grep -qE '=' ; then
            if ! echo "$line" | grep -qE '\btypedef\b' ; then
                WARNINGS=$((WARNINGS + 1))
                printf "  WARNING [ptr-init-NULL] %s:%s\n" "$file" "$lineno"
                printf "    %s\n" "$line"
            fi
        fi
    fi
done < "$ADDED_FILE"

# ── Rule 6: Use stdint.h integer types ────────────────────────────────────
echo ""
echo "--- Rule: Use stdint.h integer types ---"
while IFS=: read -r file lineno line; do
    stripped=$(echo "$line" | sed 's/^[[:space:]]*//')
    case "$stripped" in
        //*) continue ;;
        \**) continue ;;
        \#*) continue ;;
    esac
    if echo "$line" | grep -qE '(^|[[:space:];,{(])(unsigned[[:space:]]+)?(short|long long|long)[[:space:]]+[A-Za-z_]' ; then
        WARNINGS=$((WARNINGS + 1))
        printf "  WARNING [use-stdint] %s:%s\n" "$file" "$lineno"
        printf "    %s\n" "$line"
    fi
done < "$ADDED_FILE"

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
