/*
 * 0BSD-License
 *
 * (c) 2017 Laslo Hunhold <dev@frign.de>
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
#include <arpa/inet.h>

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LEN(x) (sizeof (x) / sizeof *(x))

static void
invert(uint16_t rgba[4])
{
	rgba[0] = UINT16_MAX - rgba[0];
	rgba[1] = UINT16_MAX - rgba[1];
	rgba[2] = UINT16_MAX - rgba[2];
}

int
main(int argc, char *argv[])
{
	uint32_t hdr[4], width, height, i, j, k;
	uint16_t rgba[4];

	/* arguments */
	if (argc != 1) {
		fprintf(stderr, "usage: %s\n", argv[0]);
		return 1;
	}

	/* read header */
	if (fread(hdr, sizeof(*hdr), LEN(hdr), stdin) != LEN(hdr)) {
		goto readerr;
	}
	if (memcmp("farbfeld", hdr, sizeof("farbfeld") - 1)) {
		fprintf(stderr, "%s: invalid magic value\n", argv[0]);
		return 1;
	}
	width = ntohl(hdr[2]);
	height = ntohl(hdr[3]);

	/* write data */
	if (fwrite(hdr, sizeof(*hdr), LEN(hdr), stdout) != 4) {
		goto writerr;
	}

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (fread(rgba, sizeof(*rgba), LEN(rgba),
			          stdin) != LEN(rgba)) {
				goto readerr;
			}
			for (k = 0; k < 4; k++) {
				rgba[k] = ntohs(rgba[k]);
			}

			invert(rgba);

			for (k = 0; k < 4; k++) {
				rgba[k] = htons(rgba[k]);
			}
			if (fwrite(rgba, sizeof(*rgba), LEN(rgba),
			           stdout) != LEN(rgba)) {
				goto writerr;
			}
		}
	}

	/* clean up */
	if (fclose(stdout)) {
		fprintf(stderr, "%s: fclose: %s\n", argv[0],
		        strerror(errno));
		return 1;
	}

	return 0;
readerr:
	fprintf(stderr, "%s: fread: Unexpected EOF\n", argv[0]);
	return 1;
writerr:
	fprintf(stderr, "%s: fwrite: %s\n", argv[0], strerror(errno));
	return 1;
}
