 class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#83a9e03e2d688f353acfead5ce9721ad" class="el">NETH_RESOURCE_NAME</a>   "\pNetHaspResource"</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#4a52f8fad784c0d883f9a65c14614885" class="el">NETH_RESOURCE_TYPE</a>   'NETH'</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#428d1e827e4dc939444b20bac7e9924d" class="el">NETH_RESOURCE_ID</a>   128</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#57a261e1ea3aa3ed5a4e2f0e11ffd1d2" class="el">FAS_UNLIMITED_RT</a>   0xFFFF</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="typedefs">Typedefs</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef pascal <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>(* </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#fc54579dad2b5cd56ca39c03fb126f7e" class="el">MacHaspPtr</a> )(<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>, Ptr, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef pascal short(* </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#13f4d67e433a0a7482744d564369a422" class="el">NHLoader</a> )(<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *, short, Handle)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#c7ab4602d00eebddffcde811901eacaa" class="el">MacHasp</a> (<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> Service, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> HaspNum, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> InputPrm1, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> InputPrm2, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> MemoAddr, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> MemoData, Ptr MemoBuff, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *ReturnPrm1, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *ReturnPrm2, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *Status)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal short </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#3da7660b7046316301f780f555237a42" class="el">MacHaspInit</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal short </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#6ec9c4c75f5749299d4f090e2eeadeab" class="el">MacHaspClose</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal short </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#73da20433bcfd096199e9556aac9b8c2" class="el">NetHaspInit</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal short </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#f9135bb5cd0c2d33b8fc532cd96b8618" class="el">NetHaspClose</a> (void)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

