<?php
set_include_path(get_include_path() . PATH_SEPARATOR . '../lib');

include_once('aur.inc');
check_sid();
html_header();

function getPkgs($userid) {
    $dbh = db_connect();
    $userid = mysql_real_escape_string($userid);

    $result = db_query("SELECT PackageVotes.UsersID, PackageVotes.PackageID, Packages.Name FROM PackageVotes LEFT JOIN Packages ON (Packages.ID = PackageVotes.PackageID) WHERE PackageVotes.UsersID = $userid", $dbh);

    return $result;
}

if(isset($_COOKIE['AURSID'])) {
    $acc = account_from_sid($_COOKIE['AURSID']);
} else {
    $acc = "";
}
print "<div class = 'pgbox'>";
print "<div class = 'pgboxtitle'>";
print "<span class = 'f3'>" . __("Favourite Packages") . "</span>";
print "<div class = 'pgboxbody'>";

if(!$acc) {
    print __("You must be logged in before you can view favourite packages");
    print "<br />\n";
    for($i = 0; $i < 3; $i++) {
        print "</div>";
    }

    html_footer(AUR_VERSION);
    exit();
}



$pkgs = getPkgs(uid_from_sid($_COOKIE['AURSID']));

print "<ul>";

while($row = mysql_fetch_object($pkgs)) {
    print "<li><a href=/packages.php?ID=$row->PackageID>$row->Name</a></li>";
}

print "</ul>";

print "</div>";
print "</div>";
print "</div>";


html_footer(AUR_VERSION);
