/* Music theory */

// notes in octave relative to C
G.mu_ratios = [
    1.0,
    1.05946359989,
    1.12246202207,
    1.18920625505,
    1.25992104748,
    1.33484032144,
    1.414213288,
    1.49830750508,
    1.5873981751,
    1.68179260745,
    1.7817981115,
    1.88775104577
];

G.mu_midc_freq = 261.626;
G.mu_midc_freq /= 2;

// 1-7 -> 0-11
G.mu_scale_deg_to_notenum = [
    0, // nonexistent
    0, 2, 4, 5, 7, 9, 11
];

// Given a scale degree 1-7 return frequency in key of C
G.mu_scale_deg_to_midfreq = function(sd) {
  var nn = G.mu_scale_deg_to_notenum[sd]; // 0-11
  return G.mu_midc_freq * G.mu_ratios[nn];
};

/* Return array of freqs, using inversions as needed to stay in octave */
G.mu_simple_chord_freqs = function(sd, quality, sharpness) {
  var steps = [0,4,7];
  if(quality == 'min') {
    steps[1] = 3;
  }
  var root_nn = G.mu_scale_deg_to_notenum[sd];

  if(sharpness == 'sharp') {
    root_nn ++;
  }
  else if(sharpness == 'flat') {
    root_nn --;
  }

  var rv = new Array(3);
  for(var i=0; i<3; i++) {
    var nn = (root_nn + steps[i]) % 12;
    rv[i] = G.mu_midc_freq * G.mu_ratios[nn];
  }
  return rv;
};

/* fixme - maybe refactor - so similar */
/* Return array of freqs, root position ... */
G.mu_simple_root_chord_freqs = function(sd, quality, sharpness) {
  // console.log("mu_simple_root_chord_freqs: " + sd);
  var steps = [0,4,7];
  if(quality == 'min') {
    steps[1] = 3;
  }
  var root_nn = G.mu_scale_deg_to_notenum[sd];

  if(sharpness == 'sharp') {
    console.log("mu_simple_chord_freqs: iam sharp");
    root_nn ++;
  }
  else if(sharpness == 'flat') {
    console.log("mu_simple_chord_freqs: iam flat");
    root_nn --;
  }

  var rv = new Array(3);
  for(var i=0; i<3; i++) {
    var nn = (root_nn + steps[i]) % 12;
    var octave = Math.floor((root_nn + steps[i])/12);
    rv[i] = G.mu_midc_freq * G.mu_ratios[nn] * (1 << octave);
  }
  return rv;
};
