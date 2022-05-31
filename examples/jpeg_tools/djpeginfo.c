/*
 * djpeginfo.c
 *
 * Copyright (C) 1991-1997, Thomas G. Lane.
 * Modified 2009-2019 by Guido Vollbeding.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains a command-line user interface for the JPEG decompressor.
 * It should work on any system with Unix- or MS-DOS-style command lines.
 *
 * Two different command line styles are permitted, depending on the
 * compile-time switch TWO_FILE_COMMANDLINE:
 *	djpeginfo [options]  [inputfile]
 * In the second style, output is always to standard output, which you'd
 * normally redirect to a file or pipe to some other program.  Input is
 * either from a named file or from standard input (typically redirected).
 * The second style is convenient on Unix but is unhelpful on systems that
 * don't support pipes.  Also, you MUST use the first style if your system
 * doesn't do binary I/O to stdin/stdout.
 * To simplify script writing, the "-outfile" switch is provided.  The syntax
 *	djpeginfo [options]  -outfile outputfile  inputfile
 * works regardless of which command line style is used.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "jpeglib.h"
#include <setjmp.h>

#include <ctype.h>        /* to declare isprint() */

#define READ_BINARY    "rb"
#define EXIT_SUCCESS  0

struct my_error_mgr {
  struct jpeg_error_mgr pub;    /* "public" fields */

  jmp_buf setjmp_buffer;    /* for return to caller */
};

typedef struct my_error_mgr *my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

//METHODDEF(void)
void my_error_exit(j_common_ptr cinfo) {
/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

/* Always display the message. */
/* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message)(cinfo);

/* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

/*
 * The main program.
 */

int
main(int argc, char **argv) {
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;
  FILE *infile;
  JSAMPARRAY buffer;        /* Output row buffer */
  int row_stride;        /* physical row width in output buffer */

  const char *progname = argv[0];    /* program name for error messages */

  /* Open the input file. */
  if (argc < 2) {
    printf("usage: %s image-file\n", progname);
    exit(EXIT_FAILURE);
  }

  const char *filename = argv[1];
  if ((infile = fopen(filename, READ_BINARY)) == NULL) {
    fprintf(stderr, "%s: can't open %s\n", progname, filename);
    exit(EXIT_FAILURE);
  }

  /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp(jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object, close the input file, and return.
     */
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return 0;
  }

  /* Step 1: allocate and initialize JPEG decompression object */
  jpeg_create_decompress(&cinfo);

  /* Step 2: specify data source (eg, a file) */
  jpeg_stdio_src(&cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */
  (void) jpeg_read_header(&cinfo, TRUE);

  /* Step 4: set parameters for decompression */

  /* Step 5: Start decompressor */
  (void) jpeg_start_decompress(&cinfo);

  /* JSAMPLEs per row in output buffer */
  row_stride = cinfo.output_width * cinfo.output_components;

  printf("    actual_number_of_colors   %7d  number of entries in use\n", cinfo.actual_number_of_colors);
  printf("    Adobe_transform           %7d  Color transform code from Adobe marker\n", cinfo.Adobe_transform);
  printf("    arith_code                %7d  TRUE=arithmetic coding, FALSE=Huffman\n", cinfo.arith_code);
  printf("    blocks_in_MCU             %7d  # of DCT blocks per MCU\n", cinfo.blocks_in_MCU);
  printf("    block_size                %7d  the basic DCT block size: 1..16\n", cinfo.block_size);
  printf("    buffered_image            %7d  TRUE=multiple output passes\n", cinfo.buffered_image);
  printf("    CCIR601_sampling          %7d  TRUE=first samples are cosited\n", cinfo.CCIR601_sampling);
  printf("    color_transform           %7d \n", cinfo.color_transform);
  printf("    comps_in_scan             %7d  # of JPEG components in this scan\n", cinfo.comps_in_scan);
  printf("    data_precision            %7d  bits of precision in image data\n", cinfo.data_precision);
  printf("    dct_method                %7d  IDCT algorithm selector\n", cinfo.dct_method);
  printf("    density_unit              %7d  JFIF code for pixel size units\n", cinfo.density_unit);
  printf("    desired_number_of_colors  %7d  max # colors to use in created colormap\n", cinfo.desired_number_of_colors);
  printf("    dither_mode               %7d  type of color dithering to use\n", cinfo.dither_mode);
  printf("    do_block_smoothing        %7d  TRUE=apply interblock smoothing\n", cinfo.do_block_smoothing);
  printf("    do_fancy_upsampling       %7d  TRUE=apply fancy upsampling\n", cinfo.do_fancy_upsampling);
  printf("    enable_1pass_quant        %7d  enable future use of 1-pass quantizer\n", cinfo.enable_1pass_quant);
  printf("    enable_2pass_quant        %7d  enable future use of 2-pass quantizer\n", cinfo.enable_2pass_quant);
  printf("    enable_external_quant     %7d  enable future use of external colormap\n", cinfo.enable_external_quant);
  printf("    image_height              %7d  nominal image height\n", cinfo.image_height);
  printf("    image_width               %7d  nominal image width (from SOF marker)\n", cinfo.image_width);
  printf("    input_iMCU_row            %7d  Number of iMCU rows completed\n", cinfo.input_iMCU_row);
  printf("    input_scan_number         %7d  Number of SOS markers seen so far\n", cinfo.input_scan_number);
  printf("    is_baseline               %7d  TRUE if Baseline SOF0 encountered\n", cinfo.is_baseline);
  printf("    JFIF_major_version        %7d  JFIF major version number\n", cinfo.JFIF_major_version);
  printf("    JFIF_minor_version        %7d  JFIF minor version number\n", cinfo.JFIF_minor_version);
  printf("    jpeg_color_space          %7d  colorspace of JPEG image\n", cinfo.jpeg_color_space);
  printf("    lim_Se                    %7d  min( Se, DCTSIZE2-1 ) for entropy decode\n", cinfo.lim_Se);
  printf("    max_h_samp_factor         %7d  largest h_samp_factor\n", cinfo.max_h_samp_factor);
  printf("    max_v_samp_factor         %7d  largest v_samp_factor\n", cinfo.max_v_samp_factor);
  printf("    MCU_rows_in_scan          %7d  # of MCU rows in the image\n", cinfo.MCU_rows_in_scan);
  printf("    MCUs_per_row              %7d  # of MCUs across the image\n", cinfo.MCUs_per_row);
  printf("    min_DCT_h_scaled_size     %7d  smallest DCT_h_scaled_size of any component\n", cinfo.min_DCT_h_scaled_size);
  printf("    min_DCT_v_scaled_size     %7d  smallest DCT_v_scaled_size of any component\n", cinfo.min_DCT_v_scaled_size);
  printf("    num_components            %7d  # of color components in JPEG image\n", cinfo.num_components);
  printf("    out_color_components      %7d  # of color components in out_color_space\n", cinfo.out_color_components);
  printf("    out_color_space           %7d  colorspace for output\n", cinfo.out_color_space);
  printf("    output_components         %7d  # of color components returned\n", cinfo.output_components);
  printf("    output_gamma              %7d  image gamma wanted in output\n", cinfo.output_gamma);
  printf("    output_height             %7d  scaled image height\n", cinfo.output_height);
  printf("    output_iMCU_row           %7d  Number of iMCU rows read\n", cinfo.output_iMCU_row);
  printf("    output_scanline           %7d  0 .. output_height-1\n", cinfo.output_scanline);
  printf("    output_scanline           %7d  0 .. output_height-1 \n", cinfo.output_scanline);
  printf("    output_scan_number        %7d  Nominal scan number being displayed\n", cinfo.output_scan_number);
  printf("    output_width              %7d  scaled image width\n", cinfo.output_width);
  printf("    progressive_mode          %7d  TRUE if SOFn specifies progressive mode\n", cinfo.progressive_mode);
  printf("    quantize_colors           %7d  TRUE=colormapped output wanted\n", cinfo.quantize_colors);
  printf("    raw_data_out              %7d  TRUE=downsampled data wanted\n", cinfo.raw_data_out);
  printf("    rec_outbuf_height         %7d  min recommended height of scanline buffer\n", cinfo.rec_outbuf_height);
  printf("    restart_interval          %7d  MCUs per restart interval, or 0 for no restart\n", cinfo.restart_interval);
  printf("    row_stride                %7d  JSAMPLEs per row in output buffer\n", row_stride);
  printf("    saw_Adobe_marker          %7d  TRUE iff an Adobe APP14 marker was found\n", cinfo.saw_Adobe_marker);
  printf("    saw_JFIF_marker           %7d  TRUE iff a JFIF APP0 marker was found\n", cinfo.saw_JFIF_marker);
  printf("    scale_denom               %7d  fraction by which to scale image\n", cinfo.scale_denom);
  printf("    scale_num                 %7d  fraction by which to scale image\n", cinfo.scale_num);
  printf("    total_iMCU_rows           %7d  # of iMCU rows in image\n", cinfo.total_iMCU_rows);
  printf("    two_pass_quantize         %7d  TRUE=use two-pass color quantization\n", cinfo.two_pass_quantize);
  printf("    X_density                 %7d  Horizontal pixel density\n", cinfo.X_density);
  printf("    Y_density                 %7d  Vertical pixel density\n", cinfo.Y_density);


  /* Make a one-row-high sample array that will go away when done with image */
  buffer = (*cinfo.mem->alloc_sarray)
      ((j_common_ptr) & cinfo, JPOOL_IMAGE, row_stride, 1);

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */

  /* Here we use the library's state variable cinfo.output_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   */
  while (cinfo.output_scanline < cinfo.output_height) {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
    //put_scanline_someplace(buffer[0], row_stride);
  }

  /* Step 7: Finish decompression */

  (void) jpeg_finish_decompress(&cinfo);

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(&cinfo);

  /* After finish_decompress, we can close the input file.   */
  fclose(infile);

  /* All done. */
  exit(EXIT_SUCCESS);
}
