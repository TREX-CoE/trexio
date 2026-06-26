"""Test the in-memory (RAM) back end.

The memory back end keeps the whole TREXIO file in RAM and is ephemeral: it
does not persist across open/close. Data is therefore written and read back
from the SAME open handle, exercising the same-process, disk-free exchange
path.

Skipped automatically on bindings built before the memory back end existed.
"""

import pytest
import trexio


pytestmark = pytest.mark.skipif(
    not hasattr(trexio, "TREXIO_MEMORY"),
    reason="TREXIO_MEMORY not available in this build of the bindings",
)


def test_memory_roundtrip():
    # The file name is ignored by the memory back end.
    f = trexio.File("memory_unused.py", "w", trexio.TREXIO_MEMORY)

    # dimension / numerical attribute
    trexio.write_nucleus_num(f, 3)

    # numerical dataset
    coord = [[0.0, 0.0, 0.0], [0.0, 0.0, 1.4], [0.0, 1.1, 0.0]]
    trexio.write_nucleus_coord(f, coord)

    # read it all back from the SAME handle
    assert trexio.has_nucleus_num(f)
    assert trexio.read_nucleus_num(f) == 3

    c = trexio.read_nucleus_coord(f)
    assert abs(c[1][2] - 1.4) < 1.0e-12
    assert abs(c[2][1] - 1.1) < 1.0e-12

    if f.isOpen:
        f.close()
