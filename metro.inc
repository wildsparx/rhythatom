/* Shim the requestAnimationFrame API with a setTimeout fallback;
   This provides a frequent clock to both drawing and scheduling
   audio events */
window.requestAnimFrame = (function(){
    return  window.requestAnimationFrame ||
    window.webkitRequestAnimationFrame ||
    window.mozRequestAnimationFrame ||
    window.oRequestAnimationFrame ||
    window.msRequestAnimationFrame ||
    function( callback ){
        window.setTimeout(callback, 1000 / 60);
    };
})();

/* Advance current note and time by a 16th note */

function next_note() {
    var secondsPerBeat = 60.0 / G.bpm;
    G.next_note_time += 0.25 * secondsPerBeat; // + 1/4note

    G.cur_16th_note++;    // Advance the beat number, wrap to zero
    if (G.cur_16th_note == 16) {
        G.cur_16th_note = 0;
    }
}

/* Given tic 0-15 decide if we should hear it ... */
function note_should_sound(beatNumber) {
    if ( (G.note_res==1) && (beatNumber%2))
        return false; // we're not playing non-8th 16th notes
    if ( (G.note_res==2) && (beatNumber%4))
        return false; // we're not playing non-quarter 8th notes
    return true;
}

/* Schedule a future note to both UI and sound generators */
function schedule_note( beatNumber, time ) {
    // push the note on the queue, even if we're not playing.
    G.cnvui.note_queue.push( { note: beatNumber, time: time } );
    G.chui.tic_times.push(time);

    G.chorder.tic(beatNumber, time);

    if(!note_should_sound(beatNumber)) {
      return;
    }

    var freq =
        (beatNumber % 16 === 0) ? 880.0 :
        (beatNumber % 4 === 0 ) ? 440.0 :
                                  220.0;

   var vol =
        (beatNumber % 16 === 0) ? 0.5 :
        (beatNumber % 4 === 0 ) ? 0.15 :
                                  0.05;

    G.snd.sched_snare(vol * G.percussion_vol, time, .03);
}

function schedule_events() {
    // while there are notes that will need to play before the next interval, 
    // schedule them and advance the pointer.
    while (G.next_note_time < G.actx.currentTime + G.schedule_ahead_secs ) {
        schedule_note( G.cur_16th_note, G.next_note_time );
        next_note();
    }
}

/* clicked Play button */
function on_play() {
    G.is_playing = !G.is_playing;

    if (G.is_playing) { // start playing
        G.cur_16th_note = 0;
        G.next_note_time = G.actx.currentTime;
        return "STOP";
    } else {
        G.chui.reset();
        G.chorder.reset();
        return "PLAY";
    }
}

/* Gets called frequently, roughly 60/second */

function on_timer() {
    if(G.is_playing) {
      schedule_events();
    }
    G.cnvui.draw();
    G.chui.update();
    requestAnimFrame(on_timer);
}


/* React to change in UI controls */

G.onchange = function() {
  G.chui.preflight();
  G.chords = new Array(G.nchords);
  for(var i=0; i<G.nchords; i++) {
    G.chords[i] = G.chui.get_chord(i);
    G.chords[i].freqs = G.mu_simple_chord_freqs(G.chords[i].deg, G.chords[i].qual);
  }
};

function init(){
    G.cnvui.init();
    G.snd.init();
    G.chui.set_defaults();
    G.chui.hilite_chord(0);
    G.onchange();
    requestAnimFrame(on_timer);    // start the drawing loop.
}

window.addEventListener("load", init );

