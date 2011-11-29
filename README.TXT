This module brings Google Maps API v3 to Field API and Views through jQuery LiteMaps.

Field API
=========

This module provides a new field type named "Map point" with the default widget "Map point picker".

This field is inserted as map and it allows picking a location point. The widget is configurable
through field settings form and height, width, default zoom and other options can be set.

To display the point the module creates a formatter named "Map points" that is also configurable and
shows the points selected in picker map.


Views
=====

The module supplies a new format style named "LiteMaps" that renders a map with view's nodes as map
markers. The marker popup will show the content rendered through fields selection or row mode.

To configure this, first you have to select the fields where point will be retrieved, it is not needed
add it in fields section.

After selecting fields, you have to set the map options like height, width and type.