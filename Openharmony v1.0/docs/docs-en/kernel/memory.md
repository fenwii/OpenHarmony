# Memory<a name="EN-US_TOPIC_0000001051452208"></a>

## Basic Concepts<a name="section1392116583424"></a>

Memory management is an important procedure in software development, including memory allocation, usage, and reclamation.

Sound memory management approaches and strategies help you improve software performance and reliability.

## When to Use<a name="section159581619194319"></a>

For user-space development, the OpenHarmony memory management module provides a set of APIs for you to perform memory-related operations, such as memory application, release, remapping, and attribute setting, in addition to standard APIs provided by the C library.

## Available APIs<a name="section114001032104317"></a>

**Table  1**  Standard APIs in the C library

<a name="table198502176175"></a>
<table><thead align="left"><tr id="row7850171781719"><th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.1"><p id="p23316052015"><a name="p23316052015"></a><a name="p23316052015"></a>Header File</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.2"><p id="p03417010208"><a name="p03417010208"></a><a name="p03417010208"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="p14347010207"><a name="p14347010207"></a><a name="p14347010207"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row785091771710"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p73450202019"><a name="p73450202019"></a><a name="p73450202019"></a>strings.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p934008201"><a name="p934008201"></a><a name="p934008201"></a>int bcmp(const void *s1, const void *s2, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p93412018209"><a name="p93412018209"></a><a name="p93412018209"></a>Compares byte sequences.</p>
</td>
</tr>
<tr id="row14791155651713"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p934605204"><a name="p934605204"></a><a name="p934605204"></a>strings.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p113414018209"><a name="p113414018209"></a><a name="p113414018209"></a>void bcopy(const void *src, void *dest, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p1134180102016"><a name="p1134180102016"></a><a name="p1134180102016"></a>Copies byte sequences.</p>
</td>
</tr>
<tr id="row1734319481817"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p1134900205"><a name="p1134900205"></a><a name="p1134900205"></a>strings.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p18344012207"><a name="p18344012207"></a><a name="p18344012207"></a>void bzero(void *s, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p23410042015"><a name="p23410042015"></a><a name="p23410042015"></a>Sets byte sequences to zero.</p>
</td>
</tr>
<tr id="row79226010178"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p435705201"><a name="p435705201"></a><a name="p435705201"></a>string.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p83520042019"><a name="p83520042019"></a><a name="p83520042019"></a>void *memccpy(void *dest, const void *src, int c, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p1720911419407"><a name="p1720911419407"></a><a name="p1720911419407"></a>Copies the first <strong id="b101811441468"><a name="b101811441468"></a><a name="b101811441468"></a>n</strong> bytes from the source memory area pointed to by <strong id="b418145270"><a name="b418145270"></a><a name="b418145270"></a>src</strong> to the destination memory area pointed to by <strong id="b345616258715"><a name="b345616258715"></a><a name="b345616258715"></a>dest</strong>. The copy checks whether a character specified by <strong id="b12131976813"><a name="b12131976813"></a><a name="b12131976813"></a>c</strong> is found. If <strong id="b1544713510111"><a name="b1544713510111"></a><a name="b1544713510111"></a>c</strong> is found, this function returns the next character of character <strong id="b7956205314818"><a name="b7956205314818"></a><a name="b7956205314818"></a>c</strong> in the destination memory area.</p>
</td>
</tr>
<tr id="row1992212019173"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p8355012013"><a name="p8355012013"></a><a name="p8355012013"></a>string.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p1635180162014"><a name="p1635180162014"></a><a name="p1635180162014"></a>void *memchr(const void *s, int c, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p235306203"><a name="p235306203"></a><a name="p235306203"></a>Searches for the first occurrence of the character specified by <strong id="b8237172119463"><a name="b8237172119463"></a><a name="b8237172119463"></a>c</strong> in the n-byte memory area pointed to by <strong id="b12664113004612"><a name="b12664113004612"></a><a name="b12664113004612"></a>s</strong>.</p>
</td>
</tr>
<tr id="row19231001174"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p23560172012"><a name="p23560172012"></a><a name="p23560172012"></a>string.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p1335404201"><a name="p1335404201"></a><a name="p1335404201"></a>int memcmp(const void *s1, const void *s2, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p183518092016"><a name="p183518092016"></a><a name="p183518092016"></a>Compares two memory areas.</p>
</td>
</tr>
<tr id="row189641849111717"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p758113203203"><a name="p758113203203"></a><a name="p758113203203"></a>string.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p17581112013208"><a name="p17581112013208"></a><a name="p17581112013208"></a>void *memcpy(void *dest, const void *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p1958102014208"><a name="p1958102014208"></a><a name="p1958102014208"></a>Copies <strong id="b14837192819147"><a name="b14837192819147"></a><a name="b14837192819147"></a>n</strong> bytes from the source memory area pointed to by <strong id="b193431035201416"><a name="b193431035201416"></a><a name="b193431035201416"></a>src</strong> to the destination memory area pointed to by <strong id="b14933446141410"><a name="b14933446141410"></a><a name="b14933446141410"></a>dest</strong>.</p>
</td>
</tr>
<tr id="row2964114919178"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p85811620182012"><a name="p85811620182012"></a><a name="p85811620182012"></a>string.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p3581112042013"><a name="p3581112042013"></a><a name="p3581112042013"></a>void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p4581102032018"><a name="p4581102032018"></a><a name="p4581102032018"></a>Searches for a needle string in its haystack string.</p>
</td>
</tr>
<tr id="row3965049101716"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p17581820192011"><a name="p17581820192011"></a><a name="p17581820192011"></a>string.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p1058119209207"><a name="p1058119209207"></a><a name="p1058119209207"></a>void *memmove(void *dest, const void *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p55811020162015"><a name="p55811020162015"></a><a name="p55811020162015"></a>Copies <strong id="b45021019171619"><a name="b45021019171619"></a><a name="b45021019171619"></a>n</strong> bytes from the source memory area pointed to by <strong id="b14662112810162"><a name="b14662112810162"></a><a name="b14662112810162"></a>src</strong> to the destination memory area pointed to by <strong id="b4167135171617"><a name="b4167135171617"></a><a name="b4167135171617"></a>dest</strong>.</p>
</td>
</tr>
<tr id="row12421329179"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p358112042016"><a name="p358112042016"></a><a name="p358112042016"></a>string.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p18581720102016"><a name="p18581720102016"></a><a name="p18581720102016"></a>void *mempcpy(void *dest, const void *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p25811520132017"><a name="p25811520132017"></a><a name="p25811520132017"></a>Copies <strong id="b261381131710"><a name="b261381131710"></a><a name="b261381131710"></a>n</strong> bytes from the source memory area pointed to by <strong id="b1517317471171"><a name="b1517317471171"></a><a name="b1517317471171"></a>src</strong> to the destination memory area pointed to by <strong id="b412665615172"><a name="b412665615172"></a><a name="b412665615172"></a>dest</strong>.</p>
</td>
</tr>
<tr id="row343932141715"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p358152062019"><a name="p358152062019"></a><a name="p358152062019"></a>string.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p20581720152017"><a name="p20581720152017"></a><a name="p20581720152017"></a>void *memset(void *s, int c, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p258102052019"><a name="p258102052019"></a><a name="p258102052019"></a>Copies a character to the specified memory area.</p>
</td>
</tr>
<tr id="row19344649182"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p93511010206"><a name="p93511010206"></a><a name="p93511010206"></a>stdlib.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p135180172016"><a name="p135180172016"></a><a name="p135180172016"></a>void *malloc(size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p193580102017"><a name="p193580102017"></a><a name="p193580102017"></a>Dynamically allocates a memory block of <strong id="b1522209337"><a name="b1522209337"></a><a name="b1522209337"></a>size</strong>.</p>
</td>
</tr>
<tr id="row923218311911"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p8347042018"><a name="p8347042018"></a><a name="p8347042018"></a>stdlib.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p133415072012"><a name="p133415072012"></a><a name="p133415072012"></a>void *calloc(size_t nmemb, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p2342062011"><a name="p2342062011"></a><a name="p2342062011"></a>Dynamically allocates <strong id="b17810471568"><a name="b17810471568"></a><a name="b17810471568"></a>nmemb</strong> memory blocks of <strong id="b175671554105614"><a name="b175671554105614"></a><a name="b175671554105614"></a>size</strong>.</p>
</td>
</tr>
<tr id="row612852462210"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p11582162062013"><a name="p11582162062013"></a><a name="p11582162062013"></a>stdlib.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p1558211209205"><a name="p1558211209205"></a><a name="p1558211209205"></a>void *realloc(void *ptr, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p7582172082018"><a name="p7582172082018"></a><a name="p7582172082018"></a>Changes the size of the memory block pointed to by <strong id="b369411201203"><a name="b369411201203"></a><a name="b369411201203"></a>ptr</strong> to <strong id="b17211625142015"><a name="b17211625142015"></a><a name="b17211625142015"></a>size</strong> bytes.</p>
</td>
</tr>
<tr id="row32325321910"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p15582192010204"><a name="p15582192010204"></a><a name="p15582192010204"></a>stdlib.h/malloc.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p458211205205"><a name="p458211205205"></a><a name="p458211205205"></a>void *valloc(size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p6582420192014"><a name="p6582420192014"></a><a name="p6582420192014"></a>Allocates a block of memory with the specified size and aligns the allocated memory by page size.</p>
</td>
</tr>
<tr id="row450114218205"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p93419062018"><a name="p93419062018"></a><a name="p93419062018"></a>stdlib.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p1535303201"><a name="p1535303201"></a><a name="p1535303201"></a>void free(void *ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p173511072015"><a name="p173511072015"></a><a name="p173511072015"></a>Releases the memory space pointed to by <strong id="b596650115814"><a name="b596650115814"></a><a name="b596650115814"></a>ptr</strong>.</p>
</td>
</tr>
<tr id="row96751881817"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p14351408208"><a name="p14351408208"></a><a name="p14351408208"></a>malloc.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p1735120142011"><a name="p1735120142011"></a><a name="p1735120142011"></a>size_t malloc_usable_size(void *ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p153513042014"><a name="p153513042014"></a><a name="p153513042014"></a>Obtains the size of the memory block pointed to by <strong id="b57003191449"><a name="b57003191449"></a><a name="b57003191449"></a>ptr</strong>.</p>
</td>
</tr>
<tr id="row46759851816"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p1235140172015"><a name="p1235140172015"></a><a name="p1235140172015"></a>unistd.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p4351906203"><a name="p4351906203"></a><a name="p4351906203"></a>int getpagesize(void)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p103513010204"><a name="p103513010204"></a><a name="p103513010204"></a>Obtains the page size.</p>
</td>
</tr>
<tr id="row20901907199"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p1558232032010"><a name="p1558232032010"></a><a name="p1558232032010"></a>unistd.h</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p158232012203"><a name="p158232012203"></a><a name="p158232012203"></a>void *sbrk(intptr_t increment)</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p1558212014202"><a name="p1558212014202"></a><a name="p1558212014202"></a>Changes the data segment size.</p>
</td>
</tr>
</tbody>
</table>

Details on API differences:

-   **mmap**

    **Function prototype:**

    void \*mmap\(void \*addr, size\_t length, int prot, int flags, int fd, off\_t offset\);

    **Function description:**  applies for virtual memory.

    **Parameter description:**

    <a name="table104651722114218"></a>
    <table><thead align="left"><tr id="row1346572219429"><th class="cellrowborder" valign="top" width="11.92%" id="mcps1.1.3.1.1"><p id="p146632215425"><a name="p146632215425"></a><a name="p146632215425"></a>Parameter</p>
    </th>
    <th class="cellrowborder" valign="top" width="88.08%" id="mcps1.1.3.1.2"><p id="p1446620227424"><a name="p1446620227424"></a><a name="p1446620227424"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row1346652216429"><td class="cellrowborder" valign="top" width="11.92%" headers="mcps1.1.3.1.1 "><p id="p19466122104213"><a name="p19466122104213"></a><a name="p19466122104213"></a>addr</p>
    </td>
    <td class="cellrowborder" valign="top" width="88.08%" headers="mcps1.1.3.1.2 "><p id="p1046692215426"><a name="p1046692215426"></a><a name="p1046692215426"></a>Indicates the pointer to the start address of the mapping between the virtual address space of the calling process and a file or device. If this parameter is <strong id="b146564335114"><a name="b146564335114"></a><a name="b146564335114"></a>NULL</strong>, the kernel determines the address to start (recommended). Otherwise, the portability of the program will deteriorate, because the available addresses vary depending on the OS.</p>
    </td>
    </tr>
    <tr id="row8466182274215"><td class="cellrowborder" valign="top" width="11.92%" headers="mcps1.1.3.1.1 "><p id="p5466162284220"><a name="p5466162284220"></a><a name="p5466162284220"></a>length</p>
    </td>
    <td class="cellrowborder" valign="top" width="88.08%" headers="mcps1.1.3.1.2 "><p id="p17466152214420"><a name="p17466152214420"></a><a name="p17466152214420"></a>Indicates the length of the mapping.</p>
    </td>
    </tr>
    <tr id="row154671722134211"><td class="cellrowborder" valign="top" width="11.92%" headers="mcps1.1.3.1.1 "><p id="p0467142204215"><a name="p0467142204215"></a><a name="p0467142204215"></a>prot</p>
    </td>
    <td class="cellrowborder" valign="top" width="88.08%" headers="mcps1.1.3.1.2 "><p id="p6467162234215"><a name="p6467162234215"></a><a name="p6467162234215"></a>Indicates the permission to be granted on the mapping area. The options are as follows:</p>
    <a name="ul166872913431"></a><a name="ul166872913431"></a><ul id="ul166872913431"><li><strong id="b15313055125515"><a name="b15313055125515"></a><a name="b15313055125515"></a>PROT_READ</strong>: The mapping area is readable.</li><li><strong id="b9769102785610"><a name="b9769102785610"></a><a name="b9769102785610"></a>PROT_WRITE</strong>: The mapping area is writable.</li><li><strong id="b189392043145612"><a name="b189392043145612"></a><a name="b189392043145612"></a>PROT_EXEC</strong>: The mapping area is executable.</li><li><strong id="b68771256185711"><a name="b68771256185711"></a><a name="b68771256185711"></a>PROT_NONE</strong>: The mapping area cannot be accessed.</li></ul>
    </td>
    </tr>
    <tr id="row173845488436"><td class="cellrowborder" valign="top" width="11.92%" headers="mcps1.1.3.1.1 "><p id="p1538474818437"><a name="p1538474818437"></a><a name="p1538474818437"></a>flags</p>
    </td>
    <td class="cellrowborder" valign="top" width="88.08%" headers="mcps1.1.3.1.2 "><p id="p92503134411"><a name="p92503134411"></a><a name="p92503134411"></a>Specifies whether updates are visible to other processes mapping the same segment. The options are as follows:</p>
    <a name="ul1971648144411"></a><a name="ul1971648144411"></a><ul id="ul1971648144411"><li><strong id="b4349587013"><a name="b4349587013"></a><a name="b4349587013"></a>MAP_PRIVATE</strong>: The mapping area is private, and updates to the mapping are invisible to other processes mapping the same segment.</li><li><strong id="b581433625"><a name="b581433625"></a><a name="b581433625"></a>MAP_SHARED</strong>: Updates to the mapping are visible to other processes mapping the same segment, and are stored to the disk file.</li></ul>
    </td>
    </tr>
    <tr id="row771075312437"><td class="cellrowborder" valign="top" width="11.92%" headers="mcps1.1.3.1.1 "><p id="p187105538438"><a name="p187105538438"></a><a name="p187105538438"></a>fd</p>
    </td>
    <td class="cellrowborder" valign="top" width="88.08%" headers="mcps1.1.3.1.2 "><p id="p1871005374312"><a name="p1871005374312"></a><a name="p1871005374312"></a>Indicates the file descriptor.</p>
    </td>
    </tr>
    <tr id="row1624023824419"><td class="cellrowborder" valign="top" width="11.92%" headers="mcps1.1.3.1.1 "><p id="p62406387445"><a name="p62406387445"></a><a name="p62406387445"></a>offset</p>
    </td>
    <td class="cellrowborder" valign="top" width="88.08%" headers="mcps1.1.3.1.2 "><p id="p92401382448"><a name="p92401382448"></a><a name="p92401382448"></a>Indicates the offset into the file where the mapping will start.</p>
    </td>
    </tr>
    </tbody>
    </table>

    >![](public_sys-resources/icon-note.gif) **NOTE:** 
    >For details about the implementation differences of  **mmap**  between the OS and Linux, see  [Differences from the Linux Standard Library](differences-from-the-linux-standard-library.md).

    **Return values:**

    -   Returns the pointer to the page-aligned address where the mapping is placed if the operation is successful.
    -   Returns  **\(void \*\)-1**  if the operation fails.


-   **munmap**

    **Function prototype:**

    int munmap\(void \*addr, size\_t length\);

    **Function description:**  releases virtual memory.

    **Parameter description:**

    <a name="table09071025134617"></a>
    <table><thead align="left"><tr id="row11908192513464"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p186351516144710"><a name="p186351516144710"></a><a name="p186351516144710"></a>Parameter</p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1163581610472"><a name="p1163581610472"></a><a name="p1163581610472"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row6908112512469"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p10908325194614"><a name="p10908325194614"></a><a name="p10908325194614"></a>addr</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p209081825114610"><a name="p209081825114610"></a><a name="p209081825114610"></a>Indicates the pointer to the start address of the memory region to unmap.</p>
    </td>
    </tr>
    <tr id="row2908725174617"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p29084251467"><a name="p29084251467"></a><a name="p29084251467"></a>length</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11908152510468"><a name="p11908152510468"></a><a name="p11908152510468"></a>Indicates the length of the address range to unmap.</p>
    </td>
    </tr>
    </tbody>
    </table>

    **Return values:**

    -   Returns  **0**  if the operation is successful.
    -   Returns  **-1**  if the operation fails.


-   **mprotect**

    **Function prototype:**

    int mprotect\(void \*addr, size\_t length, int prot\);

    **Function description:**  modifies the access permission on a memory region.

    **Parameter description:**

    <a name="table12636174834719"></a>
    <table><thead align="left"><tr id="row19636124813475"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p26364483473"><a name="p26364483473"></a><a name="p26364483473"></a>Parameter</p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p13636748124717"><a name="p13636748124717"></a><a name="p13636748124717"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row176369484473"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p763615487477"><a name="p763615487477"></a><a name="p763615487477"></a>addr</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1763654844715"><a name="p1763654844715"></a><a name="p1763654844715"></a>Indicates the pointer to the start address of the memory region to modify, which must be a multiple of the page size. If the access permission is abnormal, the kernel throws an exception and kills the process rather than send <strong id="b1880712519146"><a name="b1880712519146"></a><a name="b1880712519146"></a>SIGSEGV</strong> signals to the current process.</p>
    </td>
    </tr>
    <tr id="row17636134824716"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1163694824714"><a name="p1163694824714"></a><a name="p1163694824714"></a>length</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p463613482472"><a name="p463613482472"></a><a name="p463613482472"></a>Indicates the length of the memory region to modify.</p>
    </td>
    </tr>
    <tr id="row196361148184716"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8636184810477"><a name="p8636184810477"></a><a name="p8636184810477"></a>prot</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p474391424815"><a name="p474391424815"></a><a name="p474391424815"></a>Indicates the permission of the memory region to modify. The options are as follows:</p>
    <a name="ul333217192481"></a><a name="ul333217192481"></a><ul id="ul333217192481"><li><strong id="b24206816162"><a name="b24206816162"></a><a name="b24206816162"></a>PROT_READ</strong>: The memory region is readable.</li><li><strong id="b1788713791614"><a name="b1788713791614"></a><a name="b1788713791614"></a>PROT_WRITE</strong>: The memory region is writable.</li><li><strong id="b485834214166"><a name="b485834214166"></a><a name="b485834214166"></a>PROT_EXEC</strong>: The memory region is executable.</li><li><strong id="b17890174712164"><a name="b17890174712164"></a><a name="b17890174712164"></a>PROT_NONE</strong>: The memory region cannot be accessed.</li></ul>
    </td>
    </tr>
    </tbody>
    </table>

    **Return values:**

    -   Returns  **0**  if the operation is successful.
    -   Returns  **-1**  if the operation fails.


-   **mremap**

    **Function prototype:**

    void \*mremap\(void \*old\_address, size\_t old\_size, size\_t new\_size, int flags, void new\_address\);

    **Function description:**  remaps the virtual memory address.

    **Parameter description:**

    <a name="table35441821104912"></a>
    <table><thead align="left"><tr id="row19544132134919"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p205459214499"><a name="p205459214499"></a><a name="p205459214499"></a>Parameter</p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p4545102104911"><a name="p4545102104911"></a><a name="p4545102104911"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row75451321164918"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p125451321144916"><a name="p125451321144916"></a><a name="p125451321144916"></a>old_address</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554522104914"><a name="p1554522104914"></a><a name="p1554522104914"></a>Indicates the old address of the virtual memory block that needs to be expanded or shrunk. The <strong id="b1794316843610"><a name="b1794316843610"></a><a name="b1794316843610"></a>old_address</strong> must be page-aligned.</p>
    </td>
    </tr>
    <tr id="row1545172118495"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205452215498"><a name="p205452215498"></a><a name="p205452215498"></a>old_size</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954572164910"><a name="p954572164910"></a><a name="p954572164910"></a>Indicates the old size of the virtual memory block.</p>
    </td>
    </tr>
    <tr id="row1754512144913"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1854532184916"><a name="p1854532184916"></a><a name="p1854532184916"></a>new_size</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85451021164911"><a name="p85451021164911"></a><a name="p85451021164911"></a>Indicates the new size of the virtual memory block.</p>
    </td>
    </tr>
    <tr id="row1545152120497"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p145451221204913"><a name="p145451221204913"></a><a name="p145451221204913"></a>flags</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2692195864912"><a name="p2692195864912"></a><a name="p2692195864912"></a>Indicates the flags to control the remapping. If there is no sufficient space to expand the mapping in the current location, the operation will fail.</p>
    <a name="ul14935819135019"></a><a name="ul14935819135019"></a><ul id="ul14935819135019"><li><strong id="b19895113593917"><a name="b19895113593917"></a><a name="b19895113593917"></a>MREMAP_MAYMOVE</strong>: allows the kernel to relocate the mapping to a new virtual address.</li><li><strong id="b17670339134018"><a name="b17670339134018"></a><a name="b17670339134018"></a>MREMAP_FIXED</strong>: enables the <strong id="b1113314174112"><a name="b1113314174112"></a><a name="b1113314174112"></a>mremap()</strong> function to accept the fifth parameter <strong id="b2361142813419"><a name="b2361142813419"></a><a name="b2361142813419"></a>void *new_address</strong>, which specifies that the mapping address must be page-aligned. All previous mappings within the address range specified by <strong id="b19544112015421"><a name="b19544112015421"></a><a name="b19544112015421"></a>new_address</strong> and <strong id="b1540317227423"><a name="b1540317227423"></a><a name="b1540317227423"></a>new_size</strong> are unmapped. If <strong id="b8443440174218"><a name="b8443440174218"></a><a name="b8443440174218"></a>MREMAP_FIXED</strong> is specified, <strong id="b1306646204217"><a name="b1306646204217"></a><a name="b1306646204217"></a>MREMAP_MAYMOVE</strong> must also be specified.</li></ul>
    </td>
    </tr>
    </tbody>
    </table>

    **Return values:**

    -   Returns the pointer to the new virtual memory area if the operation is successful.
    -   Returns  **\(void \*\)-1**  if the operation fails.


