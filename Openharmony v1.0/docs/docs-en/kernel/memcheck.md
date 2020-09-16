# memcheck<a name="EN-US_TOPIC_0000001052170276"></a>

## Command Function<a name="section191633812516"></a>

This command is used to check whether the dynamically requested memory block is complete and whether nodes in the memory pool are damaged due to out-of-bounds memory access.

## Syntax<a name="section428816435510"></a>

memcheck

## Parameter Description<a name="section1939943304411"></a>

None

## Usage<a name="section228914491951"></a>

-   If all nodes in the memory pool are complete, "system memcheck over, all passed!" is displayed.
-   If a node in the memory pool is incomplete, information about the memory block of the damaged node is displayed.

## Example<a name="section17373205314515"></a>

Enter  **memcheck**.

## Output<a name="section13406205385413"></a>

**Figure  1**  No out-of-bounds memory access<a name="fig1115313610438"></a>  
![](figures/no-out-of-bounds-memory-access.png "no-out-of-bounds-memory-access")

**Figure  2**  Out-of-bounds memory access<a name="fig6414131084419"></a>  
![](figures/out-of-bounds-memory-access.png "out-of-bounds-memory-access")

