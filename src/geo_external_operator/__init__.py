"""
GEO External Operator.

Python interface to the native GEO geometric-response engine.
"""

from ._binding import (
    GeoResult,
    api_version,
    compute,
    find_library,
)

__all__ = [
    "GeoResult",
    "api_version",
    "compute",
    "find_library",
]

__version__ = "1.1.0"
