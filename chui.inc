/* chui = chord UI */

G.chui = {
  chord_attrs: ['beats', 'deg', 'sharp', 'qual', 'oct'],
  tic_times: [], // in seconds; timestamps of 1/16 tics coming up
  last_tic: 0, // seconds
  chord_no: 0,
  tic_no: 0,
  lit_colors: ['#000', '#7f3'],
  dark_colors: ['#000', '#160']
};

G.chui.defaults = [
  {beats: "4", deg: "1", sharp: "natural", qual: "maj", oct: "+1"},
  {beats: "4", deg: "6", sharp: "natural", qual: "min", oct: "+0"},
  {beats: "4", deg: "4", sharp: "natural", qual: "maj", oct: "+0"},
  {beats: "4", deg: "5", sharp: "natural", qual: "maj", oct: "+0"},
  {beats: "0", deg: "1", sharp: "natural", qual: "maj", oct: "+0"},
  {beats: "0", deg: "1", sharp: "natural", qual: "maj", oct: "+0"}
];

G.chui.set_defaults = function() {
  var cas = G.chui.chord_attrs;
  for(var i=0; i<G.chui.defaults.length; i++) {
    for(var j=0; j<cas.length; j++) {
      var ca = cas[j]; // e.g. beats/deg/...
      document.getElementById("chord_" + ca + "_" + i).value = G.chui.defaults[i][ca];
    }
  }
};

/* Given an index 0,1,... return chord object */

G.chui.get_chord = function(i) {
  var res = {};
  var cas = G.chui.chord_attrs;
  for(var j=0; j<cas.length; j++) {
    var ca = cas[j];
    res[ca] = document.getElementById("chord_" + ca + "_" + i).value;
  }
  return res;
};

/* Hilite the specified chord, unhiliting any previous chord in UI */
G.chui.hilite_chord = function(ind) {
  // document.getElementById("chord_ind_0").style.background='#f00';
  for(var i=0; i<G.nchords; i++) {
    var el = document.getElementById("chord_ind_" + i);
    var col = (i==ind) ? G.chui.lit_colors : G.chui.dark_colors;
    el.style.color = col[0];
    el.style.background = col[1];
  }
};

G.chui.reset = function() {
  G.chui.tic_times = [];
  G.chui.last_tic = 0;
  G.chui.chord_no = 0;
  G.chui.tic_no = 0;
  G.chui.hilite_chord(0);
}

/* call this frequently; it looks into queued notes and updates */
G.chui.update = function() {
    var currentTime = G.actx.currentTime;

    while (G.chui.tic_times.length && G.chui.tic_times[0] < currentTime) {
        G.chui.tic_times.splice(0,1);   // remove note from queue
        G.chui.tic_no ++;
        max_tics = G.chords[G.chui.chord_no].beats * 4;
        if(G.chui.tic_no >= max_tics) { // fixme
          G.chui.tic_no = 0;
          G.chui.chord_no = (G.chui.chord_no + 1) % G.nchords;
          while(G.chords[G.chui.chord_no].beats == 0) {
            G.chui.chord_no = (G.chui.chord_no + 1) % G.nchords;
          }
          G.chui.hilite_chord(G.chui.chord_no);
        }
    }
};

/* call this on_play; prevent all zero beats; returns true if need onchange */
G.chui.preflight = function() {
  var x = document.getElementById("chord_beats_0");
  if(x.value == "0") {
    x.value = "4";
    return true;
  }
  return false;
}
