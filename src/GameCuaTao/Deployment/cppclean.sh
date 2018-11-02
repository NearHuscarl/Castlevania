#!/bin/env bash

# A small script to check for c++ abundent #include directives
# Require python and git bash installed on your computer to run

set -o errexit
set -o pipefail
set -o nounset

# set -o xtrace

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd -W)"

PROJECT_ROOT="$(realpath "$SCRIPT_DIR/..")"
GAME_LIB="$PROJECT_ROOT" # Direct2DGame
SOURCES=(\
	"$PROJECT_ROOT/MarioSample" \
	"$PROJECT_ROOT/Castlevania" \
	"$PROJECT_ROOT/Direct2DGame" \
	)

lint_cpp() {
	python "$SCRIPT_DIR/../../../tools/cppclean/cppclean" \
		--include-path="$GAME_LIB" \
		"${SOURCES[@]}" &
	wait
}

print_error_msgs() {
	local error_type="$1"
	shift
	local error_msgs=("$@")

	if [[ "${#error_msgs[@]}" != 0 ]]; then
		printf '\n%s\n' "$error_type"
		printf '%s\n' "${error_msgs[@]}"
	fi
}

format_lint_result() {
	local lint_results="$1" warning_msg='' path='' warning=''

	local warning_virtual_destructor_missing=()
	local warning_prefer_forward_declaration=()
	local warning_does_not_need_include=()
	local warning_already_include=()
	local warning_static_data=()
	local warning_unable_to_find_source_file=()
	local warning_misc=()

	while read -r line; do
		line="${line//\\/\/}" # convert path sep on window from '\' to '/'
		[[ "$line" =~ (^.*)(:[0-9]+.*) ]] &&
			path="${BASH_REMATCH[1]}" &&
			warning="${BASH_REMATCH[2]}"

		warning_msg="${path#"$PROJECT_ROOT/"}$warning" # get relative path

		# categorize warnings to later print out by type of warning
		if [[ "$warning" == *'has virtual methods without a virtual dtor'* ]]; then
			warning_virtual_destructor_missing+=("$warning_msg")
		elif [[ "$warning" == *'does not need to be #included; use a forward declaration instead'* ]]; then
			warning_prefer_forward_declaration+=("$warning_msg")
		elif [[ "$warning" == *'does not need to be #included'* ]]; then
			warning_does_not_need_include+=("$warning_msg")
		elif [[ "$warning" == *'already #included in'* ]]; then
			warning_already_include+=("$warning_msg")
		elif [[ "$warning" == *'static data'* ]]; then
			warning_static_data+=("$warning_msg")
		elif [[ "$warning" == *'unable to find'* ]]; then
			warning_unable_to_find_source_file+=("$warning_msg")
		else
			warning_misc+=("$warning_msg")
		fi
	done <<< "$lint_results"

	printf 'Total Warnings: %s\n' $(("${#warning_virtual_destructor_missing[@]}" \
		+ "${#warning_prefer_forward_declaration[@]}" \
		+ "${#warning_does_not_need_include[@]}" \
		+ "${#warning_already_include[@]}" \
		+ "${#warning_static_data[@]}" \
		+ "${#warning_unable_to_find_source_file[@]}" \
		+ "${#warning_misc[@]}"))

	print_error_msgs 'VIRTUAL DTOR MISSING' "${warning_virtual_destructor_missing[@]}"
	print_error_msgs 'PREFER FORWARD DECLARATION' "${warning_prefer_forward_declaration[@]}"
	print_error_msgs 'DOES NOT NEED #INCLUDE' "${warning_does_not_need_include[@]}"
	print_error_msgs 'ALREADY #INCLUDE' "${warning_already_include[@]}"
	print_error_msgs 'STATIC DATA' "${warning_static_data[@]}"
	print_error_msgs 'UNABLE TO FIND SOURCE FILE' "${warning_unable_to_find_source_file[@]}"
	print_error_msgs 'MISC' "${warning_misc[@]}"
}

printf '' > cpplint.txt # clear old content
format_lint_result "$(lint_cpp)" >> cpplint.txt
