# Distribution<a name="EN-US_TOPIC_0000001051770842"></a>

A distribution refers to an image file of an executable OpenHarmony solution composed of a group of bundles. It contains many dependent bundles and provides scripts to illustrate how to compile and link these bundles.

Generally, a distribution does not require code but contains only the  **bundle.json**  description \(**publishAs**  set to  **distribution**\) and some compilation scripts.

As system-provided environment variables are required during distribution compiling, run the  **dist**  command in  **scripts**.

```
{
    "publishAs":"distribution",
    "scripts": {
        "dist": "script compile command"
    }
}
```

Run the following command:

```
hpm dist 
```

As it is rather complex to redefine the functionality of a distribution, OpenHarmony allows inheritance from a distribution so that you can make a tailored distribution based on the existing functionality. To inherit from a distribution, you need to define the  **base**  field in  **bundle.json**.

```
{
    "base": {
        "name": "dist_wifi_iot",
        "version": "1.0.0"
    }
}
```

In this example, the current bundle inherits from the  **dist-wifi-iot 1.0.0**  bundle of the distribution.

Each distribution consists of many dependent bundles, which are represented by the  **dependencies**  field in  **bundle.json**. Some dependencies are mandatory, and others can be added or removed required. In the  **bundle.json**  file, bundle names prefixed with a question mark \(?\) represent optional dependent bundles. If you want to inherit from a distribution involving such bundles, you can remove them and then add other bundles.

```
{
    "dependencies": {
        "?my_bundle": "1.0.0"
    }
}
```

In this example,  **my\_bundle**  is an optional dependent bundle that can be removed by using the keyword "excludes".

```
{
    "excludes": [ "my_bundle" ]
}
```

After  **my-bundle**  is removed, it will not be involved in the building process. If you forcibly remove mandatory dependent bundles, an error message will be displayed.

