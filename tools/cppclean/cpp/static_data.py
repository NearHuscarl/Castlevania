# Copyright 2008 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Print classes, functions and modules which contain static data."""

from __future__ import print_function
from __future__ import unicode_literals

import collections

from . import ast
from . import metrics


__author__ = 'nnorwitz@google.com (Neal Norwitz)'


def _find_warnings(filename, lines, ast_list, static_is_optional):
    def print_warning(node):
        for name in node.name.split(','):
            print("{}:{}: static data '{}'".format(
                filename,
                lines.get_line_number(node.start),
                name))

    def find_static(function_node):
        tokens = []
        static_found = False
        for node in function_node.body:
            if node.name == 'static':
                static_found = True

            if static_found:
                tokens.append(node)
                if node.name == ';':
                    body = list(
                        ast.ASTBuilder(iter(tokens), filename).generate())
                    _find_warnings(filename, lines, body, False)
                    tokens = []
                    static_found = False

    count = 0
    for node in ast_list:
        if isinstance(node, ast.VariableDeclaration):
            # Ignore 'static' at module scope so we can find globals too.
            is_static = 'static' in node.type.modifiers
            is_not_const = (
                'const' not in node.type.modifiers and
                'constexpr' not in node.type.modifiers
            )

            is_not_none_type = node.name is not None

            if is_not_const and (static_is_optional or is_static) and is_not_none_type:
                print_warning(node)
                count += 1
        elif isinstance(node, ast.Function) and node.body:
            find_static(node)
        elif isinstance(node, ast.Class) and node.body:
            _find_warnings(filename, lines, node.body, False)

    return count


def _get_static_declarations(ast_list):
    for node in ast_list:
        if (isinstance(node, ast.VariableDeclaration) and
                'static' in node.type.modifiers):
            for name in node.name.split(','):
                yield (name, node)


def _find_unused_static_warnings(filename, lines, ast_list):
    """Warn about unused static variables."""
    static_declarations = dict(_get_static_declarations(ast_list))

    def find_variables_use(body):
        for child in body:
            if child.name in static_declarations:
                static_use_counts[child.name] += 1

    static_use_counts = collections.Counter()
    for node in ast_list:
        if isinstance(node, ast.Function) and node.body:
            find_variables_use(node.body)
        elif isinstance(node, ast.Class) and node.body:
            for child in node.body:
                if isinstance(child, ast.Function) and child.body:
                    find_variables_use(child.body)

    count = 0
    for (name, _) in sorted(static_declarations.items(),
                            key=lambda x: x[1].start):
        if not static_use_counts[name]:
            print("{}:{}: unused variable '{}'".format(
                filename,
                lines.get_line_number(static_declarations[name].start),
                name))
            count += 1

    return count


def run(filename, source, entire_ast, include_paths,
        system_include_paths, nonsystem_include_paths, quiet):
    lines = metrics.Metrics(source)

    return (
        _find_warnings(filename, lines, entire_ast, True) +
        _find_unused_static_warnings(filename, lines, entire_ast)
    )
