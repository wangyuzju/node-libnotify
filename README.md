# the API
```
var n = new notify({
            icon: "call-start", // https://developer.gnome.org/icon-naming-spec/
            timeout: 2000, // The timeout in milliseconds.
            onClick: function(){}, // notify_notification_add_action()
        });


n.show("summary", "body");
```
