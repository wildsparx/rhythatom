<!-- Table row with controls for chord $row_num -->
<tr>
<td style="border:1px solid black" id="chord_ind_$row_num">$row_num</td>

<td><select name="chord_beats_$row_num" id="chord_beats_$row_num" onchange="G.onchange();">
  <option>4</option>
  <option>2</option>
  <option>0</option>
</select></td>

<td><select name="chord_deg_$row_num" id="chord_deg_$row_num" onchange="G.onchange();">
  <option>1</option>
  <option>2</option>
  <option>3</option>
  <option>4</option>
  <option>5</option>
  <option>6</option>
  <option>7</option>
</select></td>

<td align="center"><select name="chord_sharp_$row_num" id="chord_sharp_$row_num" onchange="G.onchange();">
  <option>natural</option>
  <option>sharp</option>
  <option>flat</option>
</select></td>

<td align="center"><select name="chord_qual_$row_num" id="chord_qual_$row_num" onchange="G.onchange();">
  <option>maj</option>
  <option>min</option>
  <option>dim</option>
</select></td>

<td align="center"><select name="chord_oct_$row_num" id="chord_oct_$row_num" onchange="G.onchange();">
  <option>+0</option>
  <option>+1</option>
  <option>-1</option>
</select></td>

</tr>
<!-- End table row with controls for chord $row_num -->

