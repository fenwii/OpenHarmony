# Bundle Version<a name="EN-US_TOPIC_0000001051612092"></a>

## Version Number Naming Specifications<a name="section16893854141310"></a>

Each version name allows only lowercase letters, which can be separated by hyphens \(-\) or underscores \(\_\). For example,  **bundle**  and  **my\_bundle**  are allowed.

A bundle version number is in the format of  _major version number_._minor version number_._revision version number_  or  _major version number_._minor version number_._revision version number_-_pre-release version number_, for example,  **1.0.0**  and  **1.0.0-beta**. For details, see  [https://semver.org](https://semver.org/).

## Version Publishing<a name="section43401320171420"></a>

You should upload bundles to the remote repository so that your peers have an option to use them. You can run the following command to upload the bundles:

```
hpm publish
```

After this command is executed, the system checks the bundle dependencies and downloads the missing dependencies. If the bundles you uploaded are in binary, the system compiles the entire bundle, generates a binary file, packs the file, and uploads it. If the bundles you uploaded are in another format, the system packs the bundle file in compliance with the defined packing rules and then uploads the file.

Note: To publish a bundle, you need an HPM account for login. After logging in to the HPM platform, register with an organization and apply for authentication. After successful authentication, you will have the permission to publish the bundle.

