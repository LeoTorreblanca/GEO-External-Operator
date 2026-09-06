"""
Backward-compatible Cobaya adapter.

The maintained implementation lives in:

    geo_external_operator.cobaya.GEOHubbleTheory

This module is retained so historical imports continue to work without
depending on private filesystem paths or a separately managed shared library.
"""

from geo_external_operator.cobaya import GEOHubbleTheory

__all__ = ["GEOHubbleTheory"]
