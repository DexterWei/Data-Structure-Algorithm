This work implements a Run-length Encoder.
Refer to the sample main.cpp for the usage.


Run-length encoded vector is a very simple form of data compression in which runs of data (that is,
sequences in which the same data value occurs in many consecutive data elements) are stored as a single
data value and count, rather than as the original run. For example, consider a raw vector
x = (1, 1, 1, 1, 1, 4, 4, 4, 2, 2, 2, 2, 8, 8)
It’s run-length encoding is a list of pairs like
[(5, 1),(3, 4),(4, 2),(2, 8)]
which means there is five “1”,followed by three “4”, followed by four “2”, followed by two “8.”

		--Professor Hsuan-Tien Lin