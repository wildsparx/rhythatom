/* Sound output using WebAudio */

G.snd = {};

G.snd.waveform_names = {
  SIN: 'sine',
  SQ:  'square',
  TRI: 'triangle',
  SAW: 'sawtooth'
};

/* populate a buffer of white noise for snares */
G.snd.create_snare_buf = function() {
    var dur = 1.0;
    G.snd.snare_buf = G.actx.createBuffer(1, dur * G.actx.sampleRate, G.actx.sampleRate);
    var buf = G.snd.snare_buf.getChannelData(0);
    var vol = 0.5;
    for(var i=0; i<G.snd.snare_buf.length; i++) {
      buf[i] = Math.random() * vol * 2 - 1;
    }
};

G.snd.init = function() {
  G.actx = new AudioContext();
  G.snd.create_snare_buf();
};

// start_time and dur are seconds; rel to AudioContext
G.snd.sched_note = function(freq, vol, start_time, dur) {
    var osc = G.actx.createOscillator();
    osc.type = G.snd.waveform_names[G.waveform];
    var gn = G.actx.createGain();
    gn.gain.value = vol;
    osc.connect(gn);
    gn.connect( G.actx.destination );
    osc.frequency.value = freq;
    if(1) {
      var attack_time = 0.01;
      gn.gain.value = 0;
      gn.gain.setValueAtTime(0, start_time);
      gn.gain.linearRampToValueAtTime(vol, start_time + attack_time);
      gn.gain.linearRampToValueAtTime(0, start_time + dur);
    }
    osc.start(start_time);
    osc.stop(start_time + dur);
};

G.snd.sched_snare = function(vol, start_time, dur) {
  var src = G.actx.createBufferSource(); // this is cheap
  var gn = G.actx.createGain();
  gn.gain.value = vol;
  src.buffer = G.snd.snare_buf;
  src.connect(gn);
  gn.connect( G.actx.destination );
  src.start(start_time);
  src.stop(start_time + dur);
}
