(function ($) {
  Drupal.behaviors.litemaps = {
    attach: function(context, settings) {
      Drupal.litemaps.init();
      Drupal.litemaps.fieldsetSummary(context);
    }
  }

  Drupal.litemaps = {};

  Drupal.litemaps = {
    init: function() {
      if (typeof Drupal.settings.litemaps == "object") {
        $.each(Drupal.settings.litemaps, function(map_id, options) {
          $('#' + map_id + ":not(.litemaps-processed)").each(function() {
            $(this).litemaps(options);
            if (options.picker) {
              var form = $(this).parents('form');

              $(this).wrap('<div class="picker" />');

              $(this).addClass('pickerk-map');
              $(this).before(
              '<div class="pickerk-input">' +
                '<div class="form-item"><input id="' + map_id + '-search" type="text" size="50" class="form-text"></div>' +
                '<div class="form-item"><input type="radio" name="type" id="' + map_id + '-changetype-all" checked="checked" class="form-radio"> <label for="' + map_id + '-changetype-all" class="option">' + Drupal.t('All') + '</label></div>' +
                '<div class="form-item"><input type="radio" name="type" id="' + map_id + '-changetype-establishment" class="form-radio"> <label for="' + map_id + '-changetype-establishment" class="option">' + Drupal.t('Establishments') + '</label></div>' +
                '<div class="form-item"><input type="radio" name="type" id="' + map_id + '-changetype-geocode" class="form-radio"> <label for="' + map_id + '-changetype-geocode" class="option">' + Drupal.t('Geocodes') + '</label></div>' +
              '</div>');

              var input = document.getElementById(map_id + '-search');
              var autocomplete = new google.maps.places.Autocomplete(input);
              var map = $(this).data('litemaps_map');
              autocomplete.bindTo('bounds', map);

              var infowindow = new google.maps.InfoWindow();

              var marker = new google.maps.Marker({
                map: map,
                icon: 'https://chart.googleapis.com/chart?chst=d_map_pin_letter_withshadow&chld=|0000FF|'
              });

              google.maps.event.addListener(marker, 'position_changed', function() {
                $('input[name="litemaps[latitude]"]', form).val(marker.getPosition().lat());
                $('input[name="litemaps[longitude]"]', form).val(marker.getPosition().lng());
              });

              google.maps.event.addListener(map, 'click', function(e) {
                infowindow.close();
                marker.setPosition(e.latLng);
              });

              google.maps.event.addListener(autocomplete, 'place_changed', function() {
                infowindow.close();
                var place = autocomplete.getPlace();
                if (place.geometry.viewport) {
                  map.fitBounds(place.geometry.viewport);
                } else {
                  map.setCenter(place.geometry.location);
                  map.setZoom(17);  // Why 17? Because it looks good.
                }

                marker.setPosition(place.geometry.location);

                var address = '';
                if (place.address_components) {
                  address = [
                    (place.address_components[0] &&
                     place.address_components[0].short_name || ''),
                    (place.address_components[1] &&
                     place.address_components[1].short_name || ''),
                    (place.address_components[2] &&
                     place.address_components[2].short_name || '')].join(' ');
                }

                infowindow.setContent('<div><b>' + place.name + '</b><br>' + address);
                infowindow.open(map, marker);
              });

              // Sets a listener on a radio button to change the filter type on Places
              // Autocomplete.
              var setupClickListener = function(id, types) {
                var radioButton = document.getElementById(id);
                google.maps.event.addDomListener(radioButton, 'click', function() {
                  autocomplete.setTypes(types);
                });
              }

              setupClickListener(map_id + '-changetype-all', []);
              setupClickListener(map_id + '-changetype-establishment', ['establishment']);
              setupClickListener(map_id + '-changetype-geocode', ['geocode']);
            }
          }).addClass('litemaps-processed');
        });
      }
    },

    fieldsetSummary: function (context) {
      $('fieldset.litemaps-node-type-settings-form', context).drupalSetSummary(function (context) {
        if ($('.form-item-litemaps-picker input').is(':checked')) {
          var summary = Drupal.t('Show location picker in node form');
        }
        else {
          var summary = Drupal.t("Don't show location picker in node form");
        }
        return Drupal.checkPlain(summary);
      });
    }
  }
}(jQuery));