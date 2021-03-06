<?php
set_include_path(get_include_path() . PATH_SEPARATOR . '../lib' . PATH_SEPARATOR . '../lang');

# This file provides support for i18n

# usage:
#   use the __() function for returning translated strings of
#   text.  The string can contain escape codes %h for HTML
#   and %s for regular text.
#
# supporting scripts:
#   there is a supporting script, web/utils/genpopo, that will
#   parse the PHP files and create PHP include files that contain
#   a mapping for each translated language.  The include files
#   have the form,
#
#     $_t["en"]["My cat is large."] = "My cat is large.";
#     $_t["es"]["My cat is large."] = "Mi gato esta grande.";
#
# examples:
#	print __("%s has %s apples.", "Bill", "5");
#	print __("This is a %hmajor%h problem!", "<b>", "</b>");

include_once('config.inc');

global $_t;

function __() {
	global $_t;
	global $LANG;

	# Create the translation.
	$args = func_get_args();

	# First argument is always string to be translated
	$tag = $args[0];

	# If there is no translation, just print the given string.
	if (empty($_t[$tag])) {
		$translated = $tag;
	}
	else {
		$translated = $_t[$tag];
	}

	$translated = htmlspecialchars($translated, ENT_QUOTES);

	$num_args = sizeof($args);

	# Subsequent arguments are strings to be formatted
	#
	# TODO: make this more robust.
	# '%%' should translate to a literal '%'

	if ( $num_args > 1 ) {
		for ($i = 1; $i < $num_args; $i++) {
			$translated = preg_replace("/\%[sh]/", $args[$i], $translated, 1);
		}
	}

	return $translated;
}

