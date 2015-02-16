/*
 * nand - interfaces for nand flash K9F2G08U0C
 *
 * Copyright (c) 2015 Eric Ju <Eric.X.Ju@gmail.com>
 * 
 * This program is free software;you can registribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;Either version 2 of
 * the License,or (at your option) any later version.
 *
 */

/*                  History
 *
 *   01/14/2015 Eric: initialization creation
 *
 */

/* init nand flash chip */
void nand_init(void);
/* read nand flash */
void nand_read(unsigned char *buf,unsigned int start_addr,unsigned int size);
