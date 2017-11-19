/* parameter serializer */
/* write_*() append bits to right side of G.pser.bits */
/* read_*() consume bits from left side of G.pser.bits */

G.pser = {
  bits: [],
  range_nbits: 7,
  ser_len: 22
};

G.pser.reset = function() {
  G.pser.bits = [];
};

/* Append an int to right end of bits */
G.pser.write_int = function(nbits, val) {
  for(var i=0; i<nbits; i++) {
    G.pser.bits.push(val & 1);
    val >>= 1;
  }
};

/* Consume an int from left end of bits */
G.pser.read_int = function(nbits) {
  var bits = G.pser.bits.splice(0, nbits);
  var res = 0;
  for(var i=0; i<nbits; i++) {
    res |= bits[i] << i;
  }
  return res;
};

/* select (dropdown) -> bits */
G.pser.write_select = function(id) {
  var el = document.getElementById(id);
  var nbits = Math.ceil(Math.log(el.length)/Math.log(2)); // bits needed
  G.pser.write_int(nbits, el.selectedIndex);
};

/* bits -> select (dropdown) */
G.pser.read_select = function(id) {
  var el = document.getElementById(id);
  var nbits = Math.ceil(Math.log(el.length)/Math.log(2)); // bits needed
  el.selectedIndex = G.pser.read_int(nbits);
};

/* range(fader) -> bits */
G.pser.write_range = function(id) {
  var r = document.getElementById(id);
  var mv = (1<<G.pser.range_nbits)-1; // 127
  var v = Math.floor(mv * (r.value - r.min) / (r.max - r.min)); // 0-127
  G.pser.write_int(7, v);
}


/* bits -> range(fader) */
G.pser.read_range = function(id) {
  var r = document.getElementById(id);
  var mv = (1<<G.pser.range_nbits)-1; // 127
  var t = G.pser.read_int(7) / mv; // 0-1
  var v = t * (r.max-r.min) + (r.min-0);
  // console.log("Gprr: " + id + " t=" + t + " v=" + v);
  r.value = v;
  r.oninput({target: {value: v}});
}

/* Return a b64 repr, consuming all bits */
G.pser.to_b64 = function() {
  /* pad to multiple of 8 */
  while((G.pser.bits.length % 8) > 0) {
    G.pser.bits.push(0);
  }
  var nbytes = G.pser.bits.length / 8;
  var bytes = Array(nbytes);
  for(var i=0; i<nbytes; i++) {
    bytes[i] = String.fromCharCode(G.pser.read_int(8));
  }
  return btoa(bytes.join(''));
};

/* Parse a b64 string, setting my bits */
G.pser.from_b64 = function(buf) {
  G.pser.reset();
  var bytes = atob(buf);
  for(var i=0; i<bytes.length; i++) {
    G.pser.write_int(8, bytes.charCodeAt(i));
  } 
};



