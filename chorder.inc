/* chorder gets a pulse on every 16th note, plays chords based on G.chords */
G.chorder = {
  tics: 0,
  chord_no: 0
};

G.chorder.reset = function() {
  G.chorder.tics = 0;
  G.chorder.chord_no = 0;
};

G.chorder.schedule_chord = function(time, strum_style) {
  var c = G.chorder;
  var noteLength = 2.0 * G.sustain * 60.0 / G.bpm; // quarter note - up to 1/2 note
  var freqs = G.mu_simple_root_chord_freqs(G.chords[c.chord_no].deg, G.chords[c.chord_no].qual);

  var oct = G.chords[c.chord_no].oct;
  var r = (oct == '-1') ? 0.5 :
          (oct == '+1') ? 2.0 :
          1.0;

  for(var i=0; i<3; i++) {
    freqs[i] *= r;
  }

  var vol = 0.2;
  strum_time = G.strum_qn * 60.0 / G.bpm; // fraction of quarter note

  if(strum_style == "DOWN") {
    for(var i=0; i<3; i++) {
      G.snd.sched_note(freqs[2-i], vol, time + strum_time * i, noteLength);
    }
  }
  else { // UP
    for(var i=0; i<3; i++) {
      G.snd.sched_note(freqs[i], vol, time + strum_time * i, noteLength);
    }
  }
  //console.log("chord_no=" + G.chui.chord_no);
}


/* beatno = 0-15, time is in future, from AudioContext */
/* gets called on every 16th note, BEFORE note plays, in order to schedule */
G.chorder.tic = function(beatno, time) {
  var c = G.chorder;
  if((c.tics % 4) == 0) { // quarter note
    strum_style = G.strum_style;
    if(strum_style == 'UP/DOWN') {
      strum_style = ((c.tics % 8) == 0) ? 'UP' : 'DOWN';
    }
    c.schedule_chord(time, strum_style);
  }
  c.tics ++;
  var ntics = G.chords[c.chord_no].beats * 4;
  if(c.tics == ntics) {
    c.tics = 0;
    c.chord_no = (c.chord_no + 1) % G.nchords;
    while(G.chords[c.chord_no].beats == 0) {
      c.chord_no = (c.chord_no + 1) % G.nchords;
    }
  }
};

