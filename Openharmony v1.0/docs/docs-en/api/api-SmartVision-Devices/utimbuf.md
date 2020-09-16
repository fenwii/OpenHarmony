# utimbuf<a name="EN-US_TOPIC_0000001055078189"></a>

## **Overview**<a name="section401696148093538"></a>

**Related Modules:**

[FS](en-us_topic_0000001055678038.md)

**Description:**

Defines the file access time and modification time. 

## **Summary**<a name="section162222307093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table704569350093538"></a>
<table><thead align="left"><tr id="row1692204794093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1326848481093538"><a name="p1326848481093538"></a><a name="p1326848481093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2053961873093538"><a name="p2053961873093538"></a><a name="p2053961873093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1189581004093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p255174632093538"><a name="p255174632093538"></a><a name="p255174632093538"></a><a href="utimbuf.md#aa39cf0bad7eff4df6239528506a557df">actime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p402274524093538"><a name="p402274524093538"></a><a name="p402274524093538"></a>time_t </p>
</td>
</tr>
<tr id="row826808324093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1415068303093538"><a name="p1415068303093538"></a><a name="p1415068303093538"></a><a href="utimbuf.md#a7588ffe699a9eda52e94aa593bf7d6d8">modtime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p969306216093538"><a name="p969306216093538"></a><a name="p969306216093538"></a>time_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section98264855093538"></a>

## **Field Documentation**<a name="section1949841249093538"></a>

## actime<a name="aa39cf0bad7eff4df6239528506a557df"></a>

```
time_t utimbuf::actime
```

 **Description:**

File access time: the last time the file was accessed 

## modtime<a name="a7588ffe699a9eda52e94aa593bf7d6d8"></a>

```
time_t utimbuf::modtime
```

 **Description:**

File modification time: the last time the file was modified 

