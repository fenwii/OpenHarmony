# Bundle Composition<a name="EN-US_TOPIC_0000001051930853"></a>

A bundle contains the following contents:

-   **src**  directory for storing code files or code library
-   **ohos\_bundles**  folder for storing dependent bundles \(It is automatically generated during bundle installation, without the need to submit to the code library.\)
-   **README.md**  file for describing the bundle
-   **bundle.json**  file for declaring metadata of the bundle
-   **LICENSE**  file for open-source code

    ```
    my-bundle
       |_ohos_bundles
       |_src
       |_bundle.json
       |_README.md
       |_LICENSE
    ```


## Code files<a name="section101483489110"></a>

Bundle code files are the same as those in a common code directory. The only difference lies in the open APIs \(declared in header files\) of a bundle, which are likely to be referenced by other bundles and need to be declared in the  **dirs**  of  **bundle.json**.

## README File<a name="section10519101221211"></a>

**README.md**  is a bundle self-description file using the markdown syntax. For details, see  [Syntax Reference](https://www.markdownguide.org/getting-started/).

To help you easily find and use the desired bundle on the HarmonyOS Package Manager \(HPM\) platform, a  **README**  file is provided in the root directory of each bundle.

The  **README**  file may include instructions on how to install, configure, and use the instance code in the bundle, as well as any other information helpful to you.

The  **README**  file is available in the bundle details page of the HPM platform.

## Metadata Description File<a name="section45511827111211"></a>

A  **bundle.json**  file describes the metadata of a bundle. Each bundle has its own  **bundle.json**  file.

```
{
  "name": "@myorg/demo-bundle",
  "version": "1.0.0",
  "license": "MIT",
  "description": "bundle description",
  "keywords": ["hos"],
  "tags": ["applications", "drivers"],
  "author": {"name":"","email":"","url":""},
  "contributors":[{"name":"","email":"","url":""},{"name":"","email":"","url":""}],
  "homepage": "http://www.foo.bar.com",
  "repository": "https://git@gitee.com:foo/bar.git",
  "publishAs": "source",
  "dirs": {
    "src": ["src/**/*.c"],
    "headers": ["headers/**/*.h"],
    "bin": ["bin/**/*.o"]
  },
  "scripts": {
    "build": "make"
  },
  "envs": {},
  "ohos": {
    "os": "2.0.0",
    "board": "hi3516",
    "kernel": "liteos-a"
  },
 "rom": "10240",
 "ram": "1024",
 "dependencies": {
    "@myorg/net":"1.0.0"
 }
}
```

Each  **bundle.json**  file has the following fields:

-   **name**: a bundle name, which starts with @ and is separated by /, for example,  **@myorg/mybundle**

-   **version**: a bundle version number, for example, 1.0.0. The version number must comply with the Semantic Versioning Specification \(SemVer\) standards.

-   **description**: a brief description of a bundle
-   **dependencies**: bundles that a bundle depends on

-   **envs**: parameters required for bundle compilation, including global parameters and dependency parameters.

-   **scripts**: commands executable to a bundle, such as those for compiling, building, testing, and burning

-   **publishAs**: bundle publishing type, which can be  **source**,  **binary**,  **distribution**, or  **code-segment**

-   **dirs**: directory structure \(such as the header file\) generated for publishing

-   **ram&rom**: statistical information about the estimated read-only memory \(ROM\) and random access memory \(RAM\) usage
-   **ohos**: mappings among OpenHarmony versions, development boards, and kernels, separated by commas \(,\).
-   Extended information: author, home page, code repository, license, tags, and keywords
-   **base**  \(only for a distribution\): a base distribution which others inherit from.

