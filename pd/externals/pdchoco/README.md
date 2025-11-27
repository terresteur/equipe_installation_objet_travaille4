# pdchoco

A collection of abstractions for Pure Data (version 0.56 and up) that requires no externals (i.e. is good with vanilla).

![pdchoco logo](./pdchco.png)

## Installation

Drop the `pdchoco` folder in your `Documents > Pd > externals` folder.

## Abstractions (V0.1)

- `ascii_parse`: Converts incoming ASCII bytes to Pd messages. It accumulates received bytes (up to 1024) and outputs the result once an end of message byte is received. Input can either be individual bytes or lists of bytes.
- `edge_trigger`: Outputs a bang when a number arrives to or leaves 0
- `either`: Input bang either goes out left or right outlet as set by right inlet (0: left, 1: right).
- `flip_flop`: Outputs the value of the internal flip flop. The flip flip values toggles between 0 and 1 on a bang.
- `f~`: Converts a float message to a signal, like sig~, but with a ramp (to avoid clicks)
- `list_accum`: Accumulates in a list all items received until a bang that outputs the contents and clears the list.
- `list_accum_lastx`: Accumulates in a list X last items received.
- `list_iterator`: Iterates the items of a list.
- `list_iterator_delayed`: Iterates the items of a list with a delay between each.
- `map`: Remap and limit input range to output range.
- `matches_start_of`: Checks if all the characters of the input match the start of the reference. Matching is done with expr and strncomp. Requires PD version >= 0.55-2
- `message_looper`: Records any type of message in time and loops them.
- `modulo`: Math modulo instead of programmer's modulo (%).
- `once`: Allows a single bang to pass. Allows another one each time a bang is received at the right inlet.
- `once_ready`: Allows a single bang to pass if a bang is received at the right inlet before.
- `param`
- `param_collect`
- `param_forward`
- `param_get`
- `param_storage`
- `scope`: Displays input values in a graphical "scope".
- `skipped_integers`: Outputs input integers and the integers between two successive inputs if some where skipped.
- `slip_pack`: Packs a list of bytes into a SLIP message.
- `slip_parse`: Parses a SLIP message into a list of bytes.
- `stream`: Generates a constant float stream
- `stream_flip_flop`: Outputs the value of the internal flip flop. The flip flip toggles value (from 0 to 1 or from 1 to 0) when the input passes from 0 to non-zero.
- `stream_smooth`: Smooth the changes in a stream of floats.
- `stream_threshold`: Outputs 1 when the input goes over the high limit and 0 when the input goes under the low limit. In betweem, outputs the previously outputed value.
- `stream_variation`: Outputs the variation between two successive values of a stream of floats.