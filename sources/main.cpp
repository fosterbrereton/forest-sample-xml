/**************************************************************************************************/

// stdc++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// stlab
#include <stlab/forest.hpp>

/**************************************************************************************************/

struct xml_node {
    using attribute = std::pair<std::string, std::string>;
    std::string _tag;
    std::vector<attribute> _attributes;
    std::string _content;
};

/**************************************************************************************************/

using xml_forest = stlab::forest<xml_node>;

/**************************************************************************************************/

void print_xml(const xml_forest& xml, std::ostream& out) {
    stlab::depth_fullorder_iterator first{xml.begin()};
    stlab::depth_fullorder_iterator last{xml.end()};

    auto indent{[&_out = out](std::size_t depth){
        constexpr auto whitespace_k{"                                                              "};
        depth = std::min(depth * 4, sizeof(whitespace_k));
        std::copy(&whitespace_k[0], &whitespace_k[depth], std::ostream_iterator<char>(_out));
    }};

    while (first != last) {
        auto has_content{!first->_content.empty()};
        if (is_leading(first)) {
            indent(first.depth());

            out << "<" << first->_tag;

            for (const auto& a : first->_attributes) {
                out << " " << a.first << "=\"" << a.second << "\"";
            }

            if (stlab::has_children(first) || has_content) {
                out << ">\n";
            } else {
                out << "/>\n";
            }

            if (has_content) {
                indent(first.depth() + 1);
                out << first->_content << '\n';
            }
        } else if (stlab::has_children(first) || has_content) {
            indent(first.depth());

            out << "</" << first->_tag << ">\n";
        }
        ++first;
    }
}

/**************************************************************************************************/

int main(int argc, const char * argv[]) try {
    xml_forest f;
    std::ofstream output("result.svg");

    auto svg = stlab::trailing_of(f.insert(f.begin(), xml_node{
        "svg", {
            { "version", "1.1" },
            { "xmlns", "http://www.w3.org/2000/svg" },
            { "xmlns:xlink", "http://www.w3.org/1999/xlink" },
            { "width", "500" },
            { "height", "500" }
        }
    }));

    auto defs = stlab::trailing_of(f.insert(svg, xml_node{ "defs" }));

    auto marker = stlab::trailing_of(f.insert(defs, xml_node{
        "marker", {
            { "id", "arrowhead" },
            { "markerWidth", "6" },
            { "markerHeight", "5" },
            { "refY", "2.5" },
            { "orient", "auto" },
        }
    }));

    f.insert(marker, xml_node{
        "polygon", {
            { "points", "0 0, 6 2.5, 0 5" },
        }
    });

    f.insert(svg, xml_node{
        "circle", {
            { "cx", "250" },
            { "cy", "250" },
            { "r", "200" },
            { "fill", "yellow" },
            { "stroke", "black" },
            { "stroke-width", "10" },
        }
    });

    f.insert(svg, xml_node{
        "circle", {
            { "cx", "175" },
            { "cy", "175" },
            { "r", "25" },
            { "fill", "black" },
            { "stroke-width", "10" },
        }
    });

    f.insert(svg, xml_node{
        "circle", {
            { "cx", "325" },
            { "cy", "175" },
            { "r", "25" },
            { "fill", "black" },
            { "stroke-width", "10" },
        }
    });

    f.insert(svg, xml_node{
        "path", {
            { "d", "M 150 300 C 150 420 360 420 360 300" },
            { "fill", "none" },
            { "stroke", "black" },
            { "stroke-width", "10" },
            { "marker-end", "url(#arrowhead)" },
        }
    });

    output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";

    print_xml(f, output);

    return EXIT_SUCCESS;
} catch (const std::exception& error) {
    std::cerr << "Fatal exception: " << error.what() << '\n';
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << "Fatal exception: unknown\n";
    return EXIT_FAILURE;
}

/**************************************************************************************************/
