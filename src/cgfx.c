#include "cgfx.h"

typedef struct CGFX_Header_s
{
	char magic[4]; // DO NOT TREAT AS STRING
	Uint16 endian;
	Uint16 header_size;
	Uint32 revision;
	Uint32 file_size;
	Uint32 entry_count;

}	CGFX_Header_t;

struct CGFX_s
{
	char * filename;
	CGFX_Header_t header;
};

CGFX CGFX_ReadFile(char * filename)
{
	char filenameBuffer[255] = {0};
	strncpy(filenameBuffer,filename,255);
	FILE * cgfxFile = fopen(filenameBuffer, "rb");
	if(!cgfxFile)
	{
		setError(ERR_CODE, ERR_NOFIL);
		return NULL;
	}

	CGFX cgfx = calloc(1,sizeof(struct CGFX_s));
	if(!cgfx)
	{
		setError(ERR_CODE, ERR_NOMEM);
		fclose(cgfxFile);
		return NULL;
	}
	sscanf(filenameBuffer,"%ms",&(cgfx->filename));

	size_t test = fread(&(cgfx->header),sizeof(CGFX_Header_t),1,cgfxFile);
	if(test != 1)
	{
		setError(ERR_MESG,"File was not valid.");
		fclose(cgfxFile);
		return NULL;
	}
	if(strncmp(cgfx->header.magic,"CGFX",4))
	{
		setError(ERR_MESG,"File did not appear to be a CGFX file.");
		fclose(cgfxFile);
		return NULL;
	}

	fclose(cgfxFile);
	return cgfx;
}

Uint32 CGFX_GetFileSize(CGFX cgfx)
{
	return cgfx->header.file_size;
}

const char * CGFX_GetMetadata(CGFX cgfx)
{
	// Desired output:
	//
	// Filename: [Filename] <- get filesize length
	// File size: [n] bytes <- size fits in 4 bytes; max length 10 digits in decimal
	// Endianness: Big/Little <- 6 chars max
	// Revision: FFFFFFFF <- 8 chars constant
	// Entry count: [n] <- 10 digits max
	size_t filenamelen = strlen(cgfx->filename);
	size_t full_length = filenamelen +
			sizeof("Filename: \n"
				   "File size: .......... bytes\n"
				   "Revision: ........\n"
				   "Entry count: ..........");

	char * meta = malloc(full_length);
	sprintf(meta,
			"Filename: %s\n"
			"File size: %d bytes\n"
			"Revision: %08x\n"
			"Entry count: %d",
			cgfx->filename,
			cgfx->header.file_size,
			cgfx->header.revision,
			cgfx->header.entry_count);
	return meta;
}