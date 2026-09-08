# Additional SDK warning review for read-only reports

Report workflow run [33931757708](https://github.com/OpenAnimationLibrary/amsdk/actions/runs/33931757708)
compiled and linked the report sources, but the warning gate correctly refused
to package them. Including the SDK scene-object headers exposed six C4244
warnings in `Include/RGBByte.h`, beyond the four previously reviewed FileCons.h
locations. The native math tests passed; no report was yet host-tested.

The archive SHA-256 remains
`0e917a67d9ac386ea3ad512ce97518f764cddc032957682717c862e64c112977`.
The exact original header source was inspected, not changed:

| Line, column | Inline operation |
| --- | --- |
| 138,18; 139,20; 140,19 | RGBByte::operator*=(float), byte red/green/blue scaling |
| 299,20 | RGBAByte::operator*=(float), byte alpha scaling |
| 473,24; 474,20 | YAByte::operator*=(float), byte luminance/alpha scaling |

These are implicit float-to-uint8 conversions before a subsequent Clamp().
Their behavior for arbitrary factors is not certified by this review. The
read-only reports use pointer traversal and float model positions, not these
color-scaling operators. They are parsed as inline bodies in included headers.

The build warning table now explicitly accepts C4244 only at these six exact
resolved SDK file/line/column locations in addition to the four FileCons.h
entries. Reports therefore retain **ten** SDK warnings in their logs/receipts;
the existing smoke source still exposes four. No compiler warning switch,
archive hash, SDK source or owned-source warning has been bypassed. A different
code/location/path is rejected by regression tests. This supplements the
foundation guide's four-warning baseline rather than certifying all SDK warnings.

A future SDK or plugin using these color operations needs its own review.
Native compile/audit/package success still does not validate the new reports
inside A:M or promote them to known-good.

## MakeaBone

MakeaBone run 34072154193 exposed the same six RGBByte.h locations. The
plugin also does not use those color-scaling operators; it obtains an existing
ColorBuf from GetColor and passes that color to AddSegment. This change reuses
the reviewed exact-location policy and its regression tests from the report
branch. SDK bytes and the general warning gate are unchanged.

The initial link also reported LNK4099 because the SDK archive does not include
Matrix_64[ d ].pdb for the non-inline Rotate2VQ implementation. MakeaBone now
uses the SDK's existing Rotate2VQ_inline implementation, avoiding that static
object dependency. LNK4099 remains rejected; no missing symbols are concealed.

## AMGLBImport

The native adapter includes the same SDK scene headers. It assigns RGBFloat
components directly and does not invoke these RGBByte scaling operators. The
existing exact-location policy is reused unchanged; other warnings remain fatal.
