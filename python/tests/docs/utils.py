from pathlib import Path

from sp_svg_diagram import _compare_svg

REFERENCE_OUTPUTS_FOLDER = Path("docs/source/_static/")


def compare_svg(doc_folder: str, svg_name: str, svg_raw: str):
    expected_svg_path = REFERENCE_OUTPUTS_FOLDER / doc_folder / (svg_name + ".svg")
    with open(expected_svg_path) as svg_file:
        expected = svg_file.read()
    assert _compare_svg(svg_raw, expected), svg_raw
