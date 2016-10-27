getdirections module for Drupal 6.x

If you have any questions or suggestions please contact me at
http://drupal.org/user/52366 or use the Getdirections issue queue.

This module provides a form to make a Google directions map.

Installation
Upload the whole getdirections directory into sites/all/modules/ or
sites/(domain)/modules/ for multisite setups.

Login to Drupal site as a user with administrative rights and go to
Administer > Site building > Modules. Scroll down to Other modules section, you
should now see Getdirections module listed there. Tick it and save configuration.

After installation go to Administer > Site configuration > Get directions and
select your preferences and Save Configuration.

If you have the gmap module installed and configured, getdirections will
use its configuration as a starting point.

Also remember to go to Administer > User management > Permissions and
set up permissions according to your needs.

If you have the location module installed you can make use of any nodes
containing location information.

For instance, if you want to "preload" the getdirections form with information
about the destination use a URL in this format:

getdirections/location/to/99

Where '99' is the node id (nid) of the location.
The user will only have to fill in the starting point.

To do it the other way around use
getdirections/location/from/99

You can also get a map with waypoints
getdirections/locations_via/1,2,3,99

If you have both the starting point and destination node ids then you can use
getdirections/locations/1/99

Where '1' is the starting point node id and 99 is the destination node id
(note the 's' in locations)

If you are using the location_user module you can make
a link to a user's location with the user id:
getdirections/location_user/to/66

Same goes for 'from'

You can also get a map with waypoints of user locations with the user ids:
getdirections/locations_user_via/1,2,3,99

You can mix nodes and users with
getdirections/location_u2n/66/99
Where 66 is is user id, 99 is node id

and vice-versa
getdirections/location_n2u/99/66
Where 66 is is user id, 99 is node id

If you have the Colorbox module installed and enabled in Get Directions
you can place any of the above paths in a colorbox iframe by replacing
'getdirections' with 'getdirections_box'.
To enable this for a link you can use the 'colorbox-load' method,
make sure that this feature has been enabled in colorbox
and use a url like this:
<a href="/getdirections_box?width=700&height=600&iframe=true" class="colorbox-load">See map</a>

or (advanced use) by adding rel="getdirectionsbox" to the url, eg
<a href="/getdirections_box" rel="getdirectionsbox">See map</a>

The last method uses the settings in admin/settings/getdirections for colorbox
and uses its own colorbox event handler, see getdirections.js. You can define your own
event handlers in your theme's javascript.
'getdirections_box' has it's own template, getdirections_box.tpl.php which can be
copied over to your theme's folder and tweaked there.

------------------
Get Directions API
These functions are for use in other modules.
There are functions available to generate these paths:

getdirections_location_path($direction, $nid)
Where $direction is either 'to' or 'from' and $nid is the node id concerned.

getdirections_locations_path($fromnid, $tonid)
Where $fromnid is the starting point and $tonid is the destination

getdirections_locations_via_path($nids)
Where $nids is a comma delimited list, eg "1,2,3,99" of node ids
Google imposes a limit of 25 points

If you have the latitude and longitude of the start and end points you can use

getdirections_locations_bylatlon($fromlocs, $fromlatlon, $tolocs, $tolatlon)
Where $fromlocs is a description of the starting point,
$fromlatlon is the latitude,longitude of the starting point
and $tolocs and $tolatlon are the same thing for the endpoint

getdirections_location_id_path($direction, $lid)
Where $direction is either 'to' or 'from' and $lid is the location id concerned.

See getdirections.api.inc for more detail.

If you are using Views and Location it will provide a 'Get driving directions' block
when you are viewing a node with a single or a user with a single location.
If you are using multiple locations per node or multiple locations per user then enable
the getdirections_multi type of view. If you are using CCK you can add the relevant
node type to the filter for that view, especially useful if you have both
'one location per node' and 'multiple locations per node' node types.

Getdirections now supports the Googlemaps API version 3, this has many new features.

The getdirections_latlon() function can be used in code or called by URL.
getdirections_latlon($direction, $latlon, $locs)
Where $direction is either 'to' or 'from', $latlon is the latitude,longitude to be used
and $locs is an optional string to describe the point being used.
The URL method would be in the form of
<a href="/getdirections/latlon/(from or to)/(lat,lon)/optional description">My Link</a>
You can also use the function getdirections_location_latlon_path() in getdirections.api.inc to
generate the string for you.

Themeing
To change the way the map is displayed you should copy the theme function you want to change
to your theme's template.php, renaming appropriately and editing it there.
see getdirections.theme.inc
There is plenty of help on themeing on drupal.org
