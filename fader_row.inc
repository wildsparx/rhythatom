<!-- ***** Table row for $label fader ***** -->
<tr>
<td class="fader_label">$label</td>
<td><div class="variable" id="show_$key">$default</div></td>
<td><input class="fader" id="fader_$key" type="range" min="$min" max="$max" step="$step" value="$default" onInput="G.$key = parseFloat(event.target.value); document.getElementById('show_$key').innerText=G.$key.toFixed($places);"></td>
</tr>
<!-- ***** End table row for $fader_label fader ***** -->
