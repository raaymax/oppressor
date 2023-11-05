extern crate gstreamer as gst;
extern crate gstreamer_video as gst_video;
extern crate gtk;
extern crate glib;
extern crate reqwest;

use gst::prelude::*;

fn main() {
    // Initialize GStreamer
    gst::init().unwrap();
    let pipeline = gst::parse_launch("playbin uri=https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm").unwrap();
    pipeline.set_state(gst::State::Playing).unwrap();
    let bus = pipeline.bus().unwrap();
    let msg = bus.timed_pop_filtered(gst::ClockTime::NONE, gst::MessageType::Error).unwrap();
}
