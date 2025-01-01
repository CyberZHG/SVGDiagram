SVG Diagram
===========

A library for rendering diagrams to SVG.

## Examples

| [![](./doc/images/example_pentagon.svg)](./tests/example/test_example_pentagon.cpp) |    |
|:-----------------------------------------------------------------------------------:|:--:|
|                                                                                     |    |

## Development

To enable tests, add the following to your CMake options:

```bash
-DGRAPH_LAYOUT_BUILD_TESTS=ON
```

## Optional Requirements

By default, this library estimates text dimensions using approximations. For more accurate measurements, PangoCairo can be enabled.

To install PangoCairo:

MacOS:

```bash
brew install cairo pango pkg-config
```

Linux:

```bash
sudo apt install libcairo2-dev libpango1.0-dev pkg-config
```

To enable PangoCairo, add the following to your CMake options:

```bash
-DSVG_DIAGRAM_ENABLE_PANGO_CAIRO=ON
```
