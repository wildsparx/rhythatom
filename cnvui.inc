/* UI for canvas-based 1/16 note step display */

G.cnvui = {
  note_queue: [],
  last_16th_note_drawn: -1,
};

G.cnvui.reset = function(e) {
    // resize the canvas - but remember - this clears the canvas too.
    G.cnvui.cnv.width = window.innerWidth;
    G.cnvui.cnv.height = window.innerHeight;

    //make sure we scroll to the top left.
    window.scrollTo(0,0); 
};

G.cnvui.draw = function() {
    var currentNote = G.cnvui.last_16th_note_drawn;
    var currentTime = G.actx.currentTime;

    while (G.cnvui.note_queue.length && G.cnvui.note_queue[0].time < currentTime) {
        currentNote = G.cnvui.note_queue[0].note;
        G.cnvui.note_queue.splice(0,1);   // remove note from queue
    }

    // We only need to draw if the note has moved.
    if (G.cnvui.last_16th_note_drawn != currentNote) {
        var x = Math.floor( G.cnvui.cnv.width / 18 );
        G.cnvui.ctx.clearRect(0,0,G.cnvui.cnv.width, G.cnvui.cnv.height); 
        for (var i=0; i<16; i++) {
            G.cnvui.ctx.fillStyle = ( currentNote == i ) ? 
                ((currentNote%4 === 0)?"red":"blue") : "black";
            G.cnvui.ctx.fillRect( x * (i+1), x, x/2, x/2 );
        }
        G.cnvui.last_16th_note_drawn = currentNote;
    }
};

G.cnvui.init = function() {
    G.cnvui.cnv = document.getElementById("cnv");
    G.cnvui.ctx = G.cnvui.cnv.getContext( '2d' );
    G.cnvui.ctx.strokeStyle = "#ffffff";
    G.cnvui.ctx.lineWidth = 2;
    window.onorientationchange = G.cnvui.reset;
    window.onresize = G.cnvui.reset;
};
  
