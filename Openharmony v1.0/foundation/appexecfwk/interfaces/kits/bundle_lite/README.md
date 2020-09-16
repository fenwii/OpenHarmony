## Introduction

- `AbilityInfo` ability information such as bundleName, srcPath(file path of one application), iconPath, isVisible etc..
- `AppexecfwkErrors` an emum including some error codes occurred when functions of `Bundle manager service` (BMS) return corresponding errors.
- `ElementName` who encapsulates bundleName, deviceId and abilityName of one application to query ability information.
- `BundleInfo` application information, including, versionName, smallIconPath, bigIconPath, iconPath, versionCode etc..
- `ModuleInfo` encapsulating moduleName, description, name, moduleType, isDeliveryInstall, deviceType and metaData.
## Directions

```
.
├── ability_info.h
├── appexecfwk_errors.h
├── bundle_info.h
├── element_name.h
├── module_info.h
└── README.md
```