# content of conftest.py
import pytest


def pytest_addoption(parser):
    parser.addoption(
        "--all", action="store_true", help="Run all back-ends"
    )


def pytest_generate_tests(metafunc):
    if "backend" in metafunc.fixturenames:
        if metafunc.config.getoption("all"):
            backends = ['hdf5', 'text']
        else:
            backends = ['text']
        metafunc.parametrize("backend", backends)
