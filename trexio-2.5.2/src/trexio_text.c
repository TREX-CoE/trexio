/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/


#include "trexio_text.h"
bool
trexio_text_file_exists (const char* file_name)
{
  /* Check if the file with "file_name" exists */
  struct stat st;

  int rc = stat(file_name, &st);

  bool file_exists = rc == 0;

  return file_exists;
}

trexio_exit_code
trexio_text_inquire (const char* file_name)
{
  /* Check if the file with "file_name" exists and that it is a directory */
  struct stat st;

  int rc = stat(file_name, &st);

  bool file_exists = rc == 0;

  if (file_exists) {

    bool is_a_directory = false;
#if defined(S_IFDIR)
    is_a_directory = st.st_mode & S_IFDIR;
#elif defined(S_ISDIR)
    is_a_directory = S_ISDIR(st.st_mode);
#else
    printf("Some important macros are missing for directory handling.\n");
    return TREXIO_FAILURE;
#endif
    if (!is_a_directory) return TREXIO_FILE_ERROR;

    return TREXIO_SUCCESS;
  } else {
    return TREXIO_FAILURE;
  }
}

#if  /* Since glibc 2.19: */ _DEFAULT_SOURCE \
           || /* Glibc 2.19 and earlier: */ _BSD_SOURCE \
           || /* Since glibc 2.10: */ _POSIX_C_SOURCE >= 200809L

/* mkdtemp is defined */
#else

char* mkdtemp(char* template) {
    char* dir = NULL;
    dir = tmpnam(dir);
    if (dir == NULL) return NULL;

    if (mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO) != 0) {
        return NULL;
    }

    strcpy(template, dir);
    return template;
}

#endif

trexio_exit_code
trexio_text_init (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* const f = (trexio_text_t*) file;

  /* Put all pointers to NULL but leave parent untouched */
  memset(&(f->parent)+1,0,sizeof(trexio_text_t)-sizeof(trexio_t));

  /* Check if directory exists */
  trexio_exit_code rc;
  rc = trexio_text_inquire(file->file_name);
  /* TREXIO file exists but is not  a directory */
  if (rc == TREXIO_FILE_ERROR) return rc;
  /* If directory does not exist - create it in write mode */
  if (rc == TREXIO_FAILURE) {

    if (file->mode == 'r') return TREXIO_READONLY;

    int rc_dir = mkdir(file->file_name, 0777);
    if (rc_dir != 0) return TREXIO_ERRNO;

  }

  /* Create the lock file in the directory */
  const char lock_file_name[] = "/.lock";

  char file_name[TREXIO_MAX_FILENAME_LENGTH];

  strncpy (file_name, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (file_name, lock_file_name, TREXIO_MAX_FILENAME_LENGTH-strlen(lock_file_name));

  if (file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    return TREXIO_LOCK_ERROR;
  }

  f->lock_file = open(file_name,O_WRONLY|O_CREAT|O_TRUNC, 0644);

  if (f->lock_file <= 0) {
    if (file->mode != 'r') {
      return TREXIO_ERRNO;
    } else {
      if (errno == EACCES) {
        /* The directory is read-only and the lock file can't be written.
          Create a dummy temporary file for dummy locking.
        */
        char dirname[TREXIO_MAX_FILENAME_LENGTH] = "/tmp/trexio.XXXXXX";
        if (mkdtemp(dirname) == NULL) return TREXIO_ERRNO;
        strncpy (file_name, dirname, TREXIO_MAX_FILENAME_LENGTH);
        file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
        strncat (file_name, lock_file_name, TREXIO_MAX_FILENAME_LENGTH-strlen(lock_file_name));
        f->lock_file = open(file_name,O_WRONLY|O_CREAT|O_TRUNC, 0644);
        remove(file_name);
        rmdir(dirname);
      } else {
        return TREXIO_ERRNO;
      }
    }
  }

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_lock(trexio_t* const file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* const f = (trexio_text_t*) file;

  struct flock fl;

  fl.l_type   = F_WRLCK;
  fl.l_whence = SEEK_SET;
  fl.l_start  = 0;
  fl.l_len    = 0;
  fl.l_pid    = getpid();

  int rc = fcntl(f->lock_file, F_SETLKW, &fl);
  if (rc == -1) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_unlock (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* const f = (trexio_text_t*) file;

  struct flock fl;

  fl.l_type   = F_UNLCK;
  fl.l_whence = SEEK_SET;
  fl.l_start  = 0;
  fl.l_len    = 0;
  fl.l_pid    = getpid();
  fcntl(f->lock_file, F_SETLK, &fl);

  close(f->lock_file);
  return TREXIO_SUCCESS;

}
trexio_exit_code
trexio_text_deinit (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  trexio_exit_code rc;

  /* Error handling for this call is added by the generator */
  rc = trexio_text_free_metadata( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_nucleus( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_cell( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_pbc( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_electron( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_state( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_basis( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_ecp( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_grid( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_ao( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_ao_1e_int( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_ao_2e_int( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_mo( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_mo_1e_int( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_mo_2e_int( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_determinant( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_csf( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_amplitude( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_rdm( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_jastrow( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_free_qmc( (trexio_text_t*) file);
  if (rc != TREXIO_SUCCESS) return rc;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  trexio_exit_code rc;
  trexio_text_t* f = (trexio_text_t*) file;

  rc = trexio_text_flush_metadata(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_nucleus(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_cell(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_pbc(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_electron(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_state(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_basis(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_ecp(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_grid(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_ao(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_ao_1e_int(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_ao_2e_int(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_mo(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_mo_1e_int(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_mo_2e_int(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_determinant(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_csf(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_amplitude(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_rdm(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_jastrow(f); if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_text_flush_qmc(f); if (rc != TREXIO_SUCCESS) return rc;

  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_has_determinant_list(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const char determinant_list_file_name[] = "/determinant_list.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, determinant_list_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(determinant_list_file_name));

  /* Check the return code of access function to determine whether the file with data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}
trexio_exit_code trexio_text_read_determinant_list(trexio_t* const file,
                                                   const int64_t offset_file,
                                                   const uint32_t rank,
                                                   const uint64_t* dims,
                                                   int64_t* const eof_read_size,
                                                   int64_t* const list)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank != 2) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (list == NULL) return TREXIO_INVALID_ARG_6;

  const char determinant_list_file_name[] = "/determinant_list.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, determinant_list_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(determinant_list_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly.
     Each 64-bit integer takes 20 slots and requires one space,

     we have int_num integers per up-spin determinant,
     then this number is doubled because we have the same number for down-spin electrons,
     and then one newline char.
   */
  uint64_t line_length = dims[1]*21UL + 1UL; // 20 digits per int64_t bitfield + 1 space = 21 spots + 1 newline char

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  /* Declare fixed buffer which will be used to read the determinant string <a1 a2 ... a/\ b1 b2 ... b\/> */
  char buffer[line_length+1];
  size_t buf_size = sizeof(buffer);
  /* Parameters to post-process the buffer and to get bit fields integers */
  uint64_t accum = 0UL;
  uint32_t shift_int64 = 21U;
  /* Counter for number of elements beind processed */
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < dims[0]; ++i) {

    accum = 0UL;
    memset(buffer, 0, buf_size);

    if (fgets(buffer, ( (int) line_length)+1, f) == NULL){

      fclose(f);
      *eof_read_size = count;
      return TREXIO_END;

    } else {

   /* The format string is not anymore static but rather dynamic (the number of ints depend on the mo_num)
      Thus, we parse the buffer string int_num*2 times to get the bit field determinants.
    */
      for (uint32_t j=0; j < (uint32_t) dims[1]; ++j) {
        rc = sscanf(buffer+accum, "%20" SCNd64, list + dims[1]*i + j);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        accum += shift_int64;
      }
      count += 1UL;

    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_determinant_list(trexio_t* const file,
                                                    const int64_t offset_file,
                                                    const uint32_t rank,
                                                    const uint64_t* dims,
                                                    const int64_t* list)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank != 2) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (list == NULL) return TREXIO_INVALID_ARG_5;

  const char determinant_list_file_name[] = "/determinant_list.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, determinant_list_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(determinant_list_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < dims[0]; ++i) {

    /* The loop below is needed to write a line with int bit fields for alpha and beta electrons */
    for (uint32_t j=0; j < (uint32_t) dims[1]; ++j) {
      rc = fprintf(f, "%20" PRId64 " ", *(list + i*dims[1] + j));
      if (rc <= 0) {
        fclose(f);
        return TREXIO_FAILURE;
      }
    }
    fprintf(f, "%s", "\n");

  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Additional part for the trexio_text_has_group to work */
  const char det_file_name[] = "/determinant.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, det_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(det_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}
trexio_exit_code
trexio_text_has_metadata (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_metadata((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char metadata_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char metadata_file_name[] = "/metadata.txt";

  strncpy (metadata_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  metadata_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (metadata_full_path, metadata_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(metadata_file_name));

  if (metadata_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(metadata_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_nucleus (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_nucleus((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char nucleus_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char nucleus_file_name[] = "/nucleus.txt";

  strncpy (nucleus_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  nucleus_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (nucleus_full_path, nucleus_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(nucleus_file_name));

  if (nucleus_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(nucleus_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_cell (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_cell((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char cell_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char cell_file_name[] = "/cell.txt";

  strncpy (cell_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  cell_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (cell_full_path, cell_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(cell_file_name));

  if (cell_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(cell_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_pbc (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_pbc((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char pbc_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char pbc_file_name[] = "/pbc.txt";

  strncpy (pbc_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  pbc_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (pbc_full_path, pbc_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(pbc_file_name));

  if (pbc_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(pbc_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_electron (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_electron((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char electron_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char electron_file_name[] = "/electron.txt";

  strncpy (electron_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  electron_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (electron_full_path, electron_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(electron_file_name));

  if (electron_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(electron_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_state (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_state((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char state_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char state_file_name[] = "/state.txt";

  strncpy (state_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  state_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (state_full_path, state_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(state_file_name));

  if (state_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(state_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_basis (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_basis((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char basis_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char basis_file_name[] = "/basis.txt";

  strncpy (basis_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  basis_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (basis_full_path, basis_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(basis_file_name));

  if (basis_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(basis_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_ecp (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_ecp((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char ecp_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char ecp_file_name[] = "/ecp.txt";

  strncpy (ecp_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  ecp_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (ecp_full_path, ecp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ecp_file_name));

  if (ecp_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(ecp_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_grid (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_grid((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char grid_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char grid_file_name[] = "/grid.txt";

  strncpy (grid_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  grid_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (grid_full_path, grid_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(grid_file_name));

  if (grid_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(grid_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_ao (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_ao((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char ao_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char ao_file_name[] = "/ao.txt";

  strncpy (ao_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  ao_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (ao_full_path, ao_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_file_name));

  if (ao_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(ao_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_ao_1e_int (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_ao_1e_int((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char ao_1e_int_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char ao_1e_int_file_name[] = "/ao_1e_int.txt";

  strncpy (ao_1e_int_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  ao_1e_int_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (ao_1e_int_full_path, ao_1e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_1e_int_file_name));

  if (ao_1e_int_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(ao_1e_int_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_ao_2e_int (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_ao_2e_int((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char ao_2e_int_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char ao_2e_int_file_name[] = "/ao_2e_int.txt";

  strncpy (ao_2e_int_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  ao_2e_int_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (ao_2e_int_full_path, ao_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_file_name));

  if (ao_2e_int_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(ao_2e_int_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_mo (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_mo((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char mo_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char mo_file_name[] = "/mo.txt";

  strncpy (mo_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  mo_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (mo_full_path, mo_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_file_name));

  if (mo_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(mo_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_mo_1e_int (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_mo_1e_int((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char mo_1e_int_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char mo_1e_int_file_name[] = "/mo_1e_int.txt";

  strncpy (mo_1e_int_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  mo_1e_int_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (mo_1e_int_full_path, mo_1e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_1e_int_file_name));

  if (mo_1e_int_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(mo_1e_int_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_mo_2e_int (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_mo_2e_int((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char mo_2e_int_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char mo_2e_int_file_name[] = "/mo_2e_int.txt";

  strncpy (mo_2e_int_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  mo_2e_int_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (mo_2e_int_full_path, mo_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_file_name));

  if (mo_2e_int_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(mo_2e_int_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_determinant (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_determinant((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char determinant_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char determinant_file_name[] = "/determinant.txt";

  strncpy (determinant_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  determinant_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (determinant_full_path, determinant_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(determinant_file_name));

  if (determinant_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(determinant_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_csf (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_csf((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char csf_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char csf_file_name[] = "/csf.txt";

  strncpy (csf_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  csf_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (csf_full_path, csf_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(csf_file_name));

  if (csf_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(csf_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_amplitude (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_amplitude((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char amplitude_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char amplitude_file_name[] = "/amplitude.txt";

  strncpy (amplitude_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  amplitude_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (amplitude_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  if (amplitude_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(amplitude_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_rdm (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_rdm((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char rdm_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char rdm_file_name[] = "/rdm.txt";

  strncpy (rdm_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  rdm_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (rdm_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  if (rdm_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(rdm_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_jastrow (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_jastrow((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char jastrow_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char jastrow_file_name[] = "/jastrow.txt";

  strncpy (jastrow_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  jastrow_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (jastrow_full_path, jastrow_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(jastrow_file_name));

  if (jastrow_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(jastrow_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_qmc (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  /* Flush the group to make sure the group.txt file is created */
  if (file->mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_qmc((trexio_text_t*) file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  /* Build the file name */
  char qmc_full_path[TREXIO_MAX_FILENAME_LENGTH];

  const char qmc_file_name[] = "/qmc.txt";

  strncpy (qmc_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  qmc_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (qmc_full_path, qmc_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(qmc_file_name));

  if (qmc_full_path[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') return TREXIO_FAILURE;

  bool file_exists;
  file_exists = trexio_text_file_exists(qmc_full_path);

  if (file_exists) {
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_free_metadata (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_metadata(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  metadata_t* metadata = file->metadata;
  if (metadata == NULL) return TREXIO_SUCCESS;


  if (metadata->metadata_code != NULL) {
    if (metadata->rank_metadata_code != 0) FREE (metadata->metadata_code[0]);
    FREE (metadata->metadata_code);
  }
  if (metadata->metadata_author != NULL) {
    if (metadata->rank_metadata_author != 0) FREE (metadata->metadata_author[0]);
    FREE (metadata->metadata_author);
  }

  if (metadata->metadata_package_version != NULL) FREE (metadata->metadata_package_version);
  if (metadata->metadata_description != NULL) FREE (metadata->metadata_description);

  FREE (metadata);
  file->metadata = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_metadata (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, metadata_t* metadata)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->metadata = metadata;
  rc_free = trexio_text_free_metadata(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_nucleus (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_nucleus(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  nucleus_t* nucleus = file->nucleus;
  if (nucleus == NULL) return TREXIO_SUCCESS;

  if (nucleus->nucleus_charge != NULL) FREE (nucleus->nucleus_charge);
  if (nucleus->nucleus_coord != NULL) FREE (nucleus->nucleus_coord);

  if (nucleus->nucleus_label != NULL) {
    if (nucleus->rank_nucleus_label != 0) FREE (nucleus->nucleus_label[0]);
    FREE (nucleus->nucleus_label);
  }

  if (nucleus->nucleus_point_group != NULL) FREE (nucleus->nucleus_point_group);

  FREE (nucleus);
  file->nucleus = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_nucleus (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, nucleus_t* nucleus)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->nucleus = nucleus;
  rc_free = trexio_text_free_nucleus(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_cell (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_cell(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  cell_t* cell = file->cell;
  if (cell == NULL) return TREXIO_SUCCESS;

  if (cell->cell_a != NULL) FREE (cell->cell_a);
  if (cell->cell_b != NULL) FREE (cell->cell_b);
  if (cell->cell_c != NULL) FREE (cell->cell_c);
  if (cell->cell_g_a != NULL) FREE (cell->cell_g_a);
  if (cell->cell_g_b != NULL) FREE (cell->cell_g_b);
  if (cell->cell_g_c != NULL) FREE (cell->cell_g_c);



  FREE (cell);
  file->cell = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_cell (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, cell_t* cell)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->cell = cell;
  rc_free = trexio_text_free_cell(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_pbc (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_pbc(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  pbc_t* pbc = file->pbc;
  if (pbc == NULL) return TREXIO_SUCCESS;

  if (pbc->pbc_k_point != NULL) FREE (pbc->pbc_k_point);
  if (pbc->pbc_k_point_weight != NULL) FREE (pbc->pbc_k_point_weight);



  FREE (pbc);
  file->pbc = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_pbc (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, pbc_t* pbc)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->pbc = pbc;
  rc_free = trexio_text_free_pbc(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_electron (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_electron(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  electron_t* electron = file->electron;
  if (electron == NULL) return TREXIO_SUCCESS;




  FREE (electron);
  file->electron = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_electron (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, electron_t* electron)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->electron = electron;
  rc_free = trexio_text_free_electron(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_state (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_state(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  state_t* state = file->state;
  if (state == NULL) return TREXIO_SUCCESS;


  if (state->state_label != NULL) {
    if (state->rank_state_label != 0) FREE (state->state_label[0]);
    FREE (state->state_label);
  }
  if (state->state_file_name != NULL) {
    if (state->rank_state_file_name != 0) FREE (state->state_file_name[0]);
    FREE (state->state_file_name);
  }

  if (state->state_current_label != NULL) FREE (state->state_current_label);

  FREE (state);
  file->state = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_state (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, state_t* state)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->state = state;
  rc_free = trexio_text_free_state(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_basis (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_basis(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  basis_t* basis = file->basis;
  if (basis == NULL) return TREXIO_SUCCESS;

  if (basis->basis_nucleus_index != NULL) FREE (basis->basis_nucleus_index);
  if (basis->basis_shell_ang_mom != NULL) FREE (basis->basis_shell_ang_mom);
  if (basis->basis_shell_factor != NULL) FREE (basis->basis_shell_factor);
  if (basis->basis_r_power != NULL) FREE (basis->basis_r_power);
  if (basis->basis_nao_grid_start != NULL) FREE (basis->basis_nao_grid_start);
  if (basis->basis_nao_grid_size != NULL) FREE (basis->basis_nao_grid_size);
  if (basis->basis_shell_index != NULL) FREE (basis->basis_shell_index);
  if (basis->basis_exponent != NULL) FREE (basis->basis_exponent);
  if (basis->basis_exponent_im != NULL) FREE (basis->basis_exponent_im);
  if (basis->basis_coefficient != NULL) FREE (basis->basis_coefficient);
  if (basis->basis_coefficient_im != NULL) FREE (basis->basis_coefficient_im);
  if (basis->basis_oscillation_arg != NULL) FREE (basis->basis_oscillation_arg);
  if (basis->basis_prim_factor != NULL) FREE (basis->basis_prim_factor);
  if (basis->basis_nao_grid_radius != NULL) FREE (basis->basis_nao_grid_radius);
  if (basis->basis_nao_grid_phi != NULL) FREE (basis->basis_nao_grid_phi);
  if (basis->basis_nao_grid_grad != NULL) FREE (basis->basis_nao_grid_grad);
  if (basis->basis_nao_grid_lap != NULL) FREE (basis->basis_nao_grid_lap);
  if (basis->basis_interpolator_phi != NULL) FREE (basis->basis_interpolator_phi);
  if (basis->basis_interpolator_grad != NULL) FREE (basis->basis_interpolator_grad);
  if (basis->basis_interpolator_lap != NULL) FREE (basis->basis_interpolator_lap);


  if (basis->basis_type != NULL) FREE (basis->basis_type);
  if (basis->basis_oscillation_kind != NULL) FREE (basis->basis_oscillation_kind);
  if (basis->basis_interpolator_kind != NULL) FREE (basis->basis_interpolator_kind);

  FREE (basis);
  file->basis = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_basis (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, basis_t* basis)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->basis = basis;
  rc_free = trexio_text_free_basis(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_ecp (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_ecp(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  ecp_t* ecp = file->ecp;
  if (ecp == NULL) return TREXIO_SUCCESS;

  if (ecp->ecp_max_ang_mom_plus_1 != NULL) FREE (ecp->ecp_max_ang_mom_plus_1);
  if (ecp->ecp_z_core != NULL) FREE (ecp->ecp_z_core);
  if (ecp->ecp_ang_mom != NULL) FREE (ecp->ecp_ang_mom);
  if (ecp->ecp_nucleus_index != NULL) FREE (ecp->ecp_nucleus_index);
  if (ecp->ecp_exponent != NULL) FREE (ecp->ecp_exponent);
  if (ecp->ecp_coefficient != NULL) FREE (ecp->ecp_coefficient);
  if (ecp->ecp_power != NULL) FREE (ecp->ecp_power);



  FREE (ecp);
  file->ecp = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_ecp (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, ecp_t* ecp)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->ecp = ecp;
  rc_free = trexio_text_free_ecp(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_grid (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_grid(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  grid_t* grid = file->grid;
  if (grid == NULL) return TREXIO_SUCCESS;

  if (grid->grid_coord != NULL) FREE (grid->grid_coord);
  if (grid->grid_weight != NULL) FREE (grid->grid_weight);
  if (grid->grid_ang_coord != NULL) FREE (grid->grid_ang_coord);
  if (grid->grid_ang_weight != NULL) FREE (grid->grid_ang_weight);
  if (grid->grid_rad_coord != NULL) FREE (grid->grid_rad_coord);
  if (grid->grid_rad_weight != NULL) FREE (grid->grid_rad_weight);


  if (grid->grid_description != NULL) FREE (grid->grid_description);

  FREE (grid);
  file->grid = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_grid (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, grid_t* grid)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->grid = grid;
  rc_free = trexio_text_free_grid(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_ao (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_ao(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  ao_t* ao = file->ao;
  if (ao == NULL) return TREXIO_SUCCESS;

  if (ao->ao_shell != NULL) FREE (ao->ao_shell);
  if (ao->ao_normalization != NULL) FREE (ao->ao_normalization);



  FREE (ao);
  file->ao = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_ao (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, ao_t* ao)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->ao = ao;
  rc_free = trexio_text_free_ao(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_ao_1e_int (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_ao_1e_int(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  ao_1e_int_t* ao_1e_int = file->ao_1e_int;
  if (ao_1e_int == NULL) return TREXIO_SUCCESS;

  if (ao_1e_int->ao_1e_int_overlap != NULL) FREE (ao_1e_int->ao_1e_int_overlap);
  if (ao_1e_int->ao_1e_int_kinetic != NULL) FREE (ao_1e_int->ao_1e_int_kinetic);
  if (ao_1e_int->ao_1e_int_potential_n_e != NULL) FREE (ao_1e_int->ao_1e_int_potential_n_e);
  if (ao_1e_int->ao_1e_int_ecp != NULL) FREE (ao_1e_int->ao_1e_int_ecp);
  if (ao_1e_int->ao_1e_int_core_hamiltonian != NULL) FREE (ao_1e_int->ao_1e_int_core_hamiltonian);
  if (ao_1e_int->ao_1e_int_overlap_im != NULL) FREE (ao_1e_int->ao_1e_int_overlap_im);
  if (ao_1e_int->ao_1e_int_kinetic_im != NULL) FREE (ao_1e_int->ao_1e_int_kinetic_im);
  if (ao_1e_int->ao_1e_int_potential_n_e_im != NULL) FREE (ao_1e_int->ao_1e_int_potential_n_e_im);
  if (ao_1e_int->ao_1e_int_ecp_im != NULL) FREE (ao_1e_int->ao_1e_int_ecp_im);
  if (ao_1e_int->ao_1e_int_core_hamiltonian_im != NULL) FREE (ao_1e_int->ao_1e_int_core_hamiltonian_im);



  FREE (ao_1e_int);
  file->ao_1e_int = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_ao_1e_int (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, ao_1e_int_t* ao_1e_int)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->ao_1e_int = ao_1e_int;
  rc_free = trexio_text_free_ao_1e_int(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_ao_2e_int (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_ao_2e_int(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  ao_2e_int_t* ao_2e_int = file->ao_2e_int;
  if (ao_2e_int == NULL) return TREXIO_SUCCESS;




  FREE (ao_2e_int);
  file->ao_2e_int = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_ao_2e_int (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, ao_2e_int_t* ao_2e_int)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->ao_2e_int = ao_2e_int;
  rc_free = trexio_text_free_ao_2e_int(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_mo (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_mo(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  mo_t* mo = file->mo;
  if (mo == NULL) return TREXIO_SUCCESS;

  if (mo->mo_coefficient != NULL) FREE (mo->mo_coefficient);
  if (mo->mo_coefficient_im != NULL) FREE (mo->mo_coefficient_im);
  if (mo->mo_occupation != NULL) FREE (mo->mo_occupation);
  if (mo->mo_energy != NULL) FREE (mo->mo_energy);
  if (mo->mo_spin != NULL) FREE (mo->mo_spin);
  if (mo->mo_k_point != NULL) FREE (mo->mo_k_point);

  if (mo->mo_class != NULL) {
    if (mo->rank_mo_class != 0) FREE (mo->mo_class[0]);
    FREE (mo->mo_class);
  }
  if (mo->mo_symmetry != NULL) {
    if (mo->rank_mo_symmetry != 0) FREE (mo->mo_symmetry[0]);
    FREE (mo->mo_symmetry);
  }

  if (mo->mo_type != NULL) FREE (mo->mo_type);

  FREE (mo);
  file->mo = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_mo (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, mo_t* mo)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->mo = mo;
  rc_free = trexio_text_free_mo(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_mo_1e_int (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_mo_1e_int(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  mo_1e_int_t* mo_1e_int = file->mo_1e_int;
  if (mo_1e_int == NULL) return TREXIO_SUCCESS;

  if (mo_1e_int->mo_1e_int_overlap != NULL) FREE (mo_1e_int->mo_1e_int_overlap);
  if (mo_1e_int->mo_1e_int_kinetic != NULL) FREE (mo_1e_int->mo_1e_int_kinetic);
  if (mo_1e_int->mo_1e_int_potential_n_e != NULL) FREE (mo_1e_int->mo_1e_int_potential_n_e);
  if (mo_1e_int->mo_1e_int_ecp != NULL) FREE (mo_1e_int->mo_1e_int_ecp);
  if (mo_1e_int->mo_1e_int_core_hamiltonian != NULL) FREE (mo_1e_int->mo_1e_int_core_hamiltonian);
  if (mo_1e_int->mo_1e_int_overlap_im != NULL) FREE (mo_1e_int->mo_1e_int_overlap_im);
  if (mo_1e_int->mo_1e_int_kinetic_im != NULL) FREE (mo_1e_int->mo_1e_int_kinetic_im);
  if (mo_1e_int->mo_1e_int_potential_n_e_im != NULL) FREE (mo_1e_int->mo_1e_int_potential_n_e_im);
  if (mo_1e_int->mo_1e_int_ecp_im != NULL) FREE (mo_1e_int->mo_1e_int_ecp_im);
  if (mo_1e_int->mo_1e_int_core_hamiltonian_im != NULL) FREE (mo_1e_int->mo_1e_int_core_hamiltonian_im);



  FREE (mo_1e_int);
  file->mo_1e_int = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_mo_1e_int (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, mo_1e_int_t* mo_1e_int)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->mo_1e_int = mo_1e_int;
  rc_free = trexio_text_free_mo_1e_int(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_mo_2e_int (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_mo_2e_int(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  mo_2e_int_t* mo_2e_int = file->mo_2e_int;
  if (mo_2e_int == NULL) return TREXIO_SUCCESS;




  FREE (mo_2e_int);
  file->mo_2e_int = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_mo_2e_int (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, mo_2e_int_t* mo_2e_int)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->mo_2e_int = mo_2e_int;
  rc_free = trexio_text_free_mo_2e_int(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_determinant (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_determinant(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  determinant_t* determinant = file->determinant;
  if (determinant == NULL) return TREXIO_SUCCESS;




  FREE (determinant);
  file->determinant = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_determinant (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, determinant_t* determinant)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->determinant = determinant;
  rc_free = trexio_text_free_determinant(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_csf (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_csf(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  csf_t* csf = file->csf;
  if (csf == NULL) return TREXIO_SUCCESS;




  FREE (csf);
  file->csf = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_csf (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, csf_t* csf)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->csf = csf;
  rc_free = trexio_text_free_csf(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_amplitude (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_amplitude(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  amplitude_t* amplitude = file->amplitude;
  if (amplitude == NULL) return TREXIO_SUCCESS;




  FREE (amplitude);
  file->amplitude = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_amplitude (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, amplitude_t* amplitude)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->amplitude = amplitude;
  rc_free = trexio_text_free_amplitude(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_rdm (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_rdm(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  rdm_t* rdm = file->rdm;
  if (rdm == NULL) return TREXIO_SUCCESS;

  if (rdm->rdm_1e != NULL) FREE (rdm->rdm_1e);
  if (rdm->rdm_1e_up != NULL) FREE (rdm->rdm_1e_up);
  if (rdm->rdm_1e_dn != NULL) FREE (rdm->rdm_1e_dn);
  if (rdm->rdm_1e_transition != NULL) FREE (rdm->rdm_1e_transition);



  FREE (rdm);
  file->rdm = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_rdm (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, rdm_t* rdm)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->rdm = rdm;
  rc_free = trexio_text_free_rdm(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_jastrow (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_jastrow(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  jastrow_t* jastrow = file->jastrow;
  if (jastrow == NULL) return TREXIO_SUCCESS;

  if (jastrow->jastrow_en != NULL) FREE (jastrow->jastrow_en);
  if (jastrow->jastrow_ee != NULL) FREE (jastrow->jastrow_ee);
  if (jastrow->jastrow_een != NULL) FREE (jastrow->jastrow_een);
  if (jastrow->jastrow_en_nucleus != NULL) FREE (jastrow->jastrow_en_nucleus);
  if (jastrow->jastrow_een_nucleus != NULL) FREE (jastrow->jastrow_een_nucleus);
  if (jastrow->jastrow_en_scaling != NULL) FREE (jastrow->jastrow_en_scaling);


  if (jastrow->jastrow_type != NULL) FREE (jastrow->jastrow_type);

  FREE (jastrow);
  file->jastrow = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_jastrow (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, jastrow_t* jastrow)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->jastrow = jastrow;
  rc_free = trexio_text_free_jastrow(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_free_qmc (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode != 'r') {
    trexio_exit_code rc = trexio_text_flush_qmc(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  qmc_t* qmc = file->qmc;
  if (qmc == NULL) return TREXIO_SUCCESS;

  if (qmc->qmc_point != NULL) FREE (qmc->qmc_point);
  if (qmc->qmc_psi != NULL) FREE (qmc->qmc_psi);
  if (qmc->qmc_e_loc != NULL) FREE (qmc->qmc_e_loc);



  FREE (qmc);
  file->qmc = NULL;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_free_read_qmc (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, qmc_t* qmc)
{
  trexio_exit_code rc_free;

  FREE(buffer);
  fclose(txt_file);
  /* Set pointer to the struct so that the garbage collector can do the job on file handle */
  trexio_file->qmc = qmc;
  rc_free = trexio_text_free_qmc(trexio_file);
  assert(rc_free == TREXIO_SUCCESS);

  return TREXIO_SUCCESS;
}

metadata_t*
trexio_text_read_metadata (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->metadata != NULL) {
    return file->metadata;
  }

  /* Allocate the data structure */
  metadata_t* metadata = MALLOC(metadata_t);
  if (metadata == NULL) return NULL;

  memset(metadata,0,sizeof(metadata_t));

  /* Build the file name */
  const char metadata_file_name[] = "/metadata.txt";

  strncpy (metadata->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  metadata->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (metadata->file_name, metadata_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(metadata_file_name));

  if (metadata->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(metadata);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(metadata->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(metadata);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_metadata_code = 0;
    uint64_t size_metadata_author = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_metadata_code") == 0) {

        rc = fscanf(f, "%u", &(metadata->rank_metadata_code));
        if (rc != 1) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        if (metadata->rank_metadata_code != 0) size_metadata_code = 1UL;

        for (uint32_t i=0; i<metadata->rank_metadata_code; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_metadata_code") != 0) || (j!=i)) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(metadata->dims_metadata_code[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          size_metadata_code *= metadata->dims_metadata_code[i];
        }
      } else if (strcmp(buffer, "rank_metadata_author") == 0) {

        rc = fscanf(f, "%u", &(metadata->rank_metadata_author));
        if (rc != 1) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        if (metadata->rank_metadata_author != 0) size_metadata_author = 1UL;

        for (uint32_t i=0; i<metadata->rank_metadata_author; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_metadata_author") != 0) || (j!=i)) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(metadata->dims_metadata_author[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          size_metadata_author *= metadata->dims_metadata_author[i];
        }
      } else if (strcmp(buffer, "metadata_code") == 0) {

        if (size_metadata_code != 0) {
          /* Allocate arrays */
          metadata->metadata_code = CALLOC(size_metadata_code, char*);
          if (metadata->metadata_code == NULL) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          /* WARNING: this tmp array allows to avoid allocation of space for each element of array of string
           * BUT it's size has to be number_of_str*max_len_str where max_len_str is somewhat arbitrary, e.g. 32.
           */
          char* tmp_metadata_code;
          tmp_metadata_code = CALLOC(size_metadata_code*32, char);

          for (uint64_t i=0 ; i<size_metadata_code ; ++i) {
            metadata->metadata_code[i] = tmp_metadata_code;
            /* conventional fcanf with "%s" only return the string before the first space character
             * to read string with spaces use "%[^\n]" possible with space before or after, i.e. " %[^\n]"
             */
            rc = fscanf(f, " %1023[^\n]", buffer);
            if (rc != 1) {
              trexio_text_free_read_metadata(buffer, f, file, metadata);
              return NULL;
            }

            size_t tmp_metadata_code_len = strlen(buffer);
            strncpy(tmp_metadata_code, buffer, 32);
            tmp_metadata_code[31] = '\0';
            tmp_metadata_code += tmp_metadata_code_len + 1;
          }
        }

      } else if (strcmp(buffer, "metadata_author") == 0) {

        if (size_metadata_author != 0) {
          /* Allocate arrays */
          metadata->metadata_author = CALLOC(size_metadata_author, char*);
          if (metadata->metadata_author == NULL) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          /* WARNING: this tmp array allows to avoid allocation of space for each element of array of string
           * BUT it's size has to be number_of_str*max_len_str where max_len_str is somewhat arbitrary, e.g. 32.
           */
          char* tmp_metadata_author;
          tmp_metadata_author = CALLOC(size_metadata_author*32, char);

          for (uint64_t i=0 ; i<size_metadata_author ; ++i) {
            metadata->metadata_author[i] = tmp_metadata_author;
            /* conventional fcanf with "%s" only return the string before the first space character
             * to read string with spaces use "%[^\n]" possible with space before or after, i.e. " %[^\n]"
             */
            rc = fscanf(f, " %1023[^\n]", buffer);
            if (rc != 1) {
              trexio_text_free_read_metadata(buffer, f, file, metadata);
              return NULL;
            }

            size_t tmp_metadata_author_len = strlen(buffer);
            strncpy(tmp_metadata_author, buffer, 32);
            tmp_metadata_author[31] = '\0';
            tmp_metadata_author += tmp_metadata_author_len + 1;
          }
        }

      } else if (strcmp(buffer, "metadata_code_num_isSet") == 0) {

        unsigned int metadata_code_num_isSet;
        /* additional parameter metadata_code_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(metadata_code_num_isSet));
        metadata->metadata_code_num_isSet = (bool) metadata_code_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        if (metadata->metadata_code_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "metadata_code_num") != 0)) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(metadata->metadata_code_num));
          if (rc != 1) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "metadata_author_num_isSet") == 0) {

        unsigned int metadata_author_num_isSet;
        /* additional parameter metadata_author_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(metadata_author_num_isSet));
        metadata->metadata_author_num_isSet = (bool) metadata_author_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        if (metadata->metadata_author_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "metadata_author_num") != 0)) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(metadata->metadata_author_num));
          if (rc != 1) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "metadata_unsafe_isSet") == 0) {

        unsigned int metadata_unsafe_isSet;
        /* additional parameter metadata_unsafe_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(metadata_unsafe_isSet));
        metadata->metadata_unsafe_isSet = (bool) metadata_unsafe_isSet;
        if (rc != 1) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        if (metadata->metadata_unsafe_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "metadata_unsafe") != 0)) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(metadata->metadata_unsafe));
          if (rc != 1) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "len_metadata_package_version") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(metadata->len_metadata_package_version));
        if (rc != 1) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "metadata_package_version") != 0)) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        if (metadata->len_metadata_package_version != 0) {

          metadata->metadata_package_version = CALLOC(metadata->len_metadata_package_version, char);
          if (metadata->metadata_package_version == NULL) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(metadata->metadata_package_version, buffer, metadata->len_metadata_package_version);
          metadata->metadata_package_version[metadata->len_metadata_package_version-1] = '\0';

        }
      } else if (strcmp(buffer, "len_metadata_description") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(metadata->len_metadata_description));
        if (rc != 1) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "metadata_description") != 0)) {
          trexio_text_free_read_metadata(buffer, f, file, metadata);
          return NULL;
        }

        if (metadata->len_metadata_description != 0) {

          metadata->metadata_description = CALLOC(metadata->len_metadata_description, char);
          if (metadata->metadata_description == NULL) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_metadata(buffer, f, file, metadata);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(metadata->metadata_description, buffer, metadata->len_metadata_description);
          metadata->metadata_description[metadata->len_metadata_description-1] = '\0';

        }
      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->metadata = metadata;
  return metadata;
}

nucleus_t*
trexio_text_read_nucleus (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->nucleus != NULL) {
    return file->nucleus;
  }

  /* Allocate the data structure */
  nucleus_t* nucleus = MALLOC(nucleus_t);
  if (nucleus == NULL) return NULL;

  memset(nucleus,0,sizeof(nucleus_t));

  /* Build the file name */
  const char nucleus_file_name[] = "/nucleus.txt";

  strncpy (nucleus->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  nucleus->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (nucleus->file_name, nucleus_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(nucleus_file_name));

  if (nucleus->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(nucleus);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(nucleus->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(nucleus);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_nucleus_charge = 0;
    uint64_t size_nucleus_coord = 0;
    uint64_t size_nucleus_label = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_nucleus_charge") == 0) {

        rc = fscanf(f, "%u", &(nucleus->rank_nucleus_charge));
        if (rc != 1) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        if (nucleus->rank_nucleus_charge != 0) size_nucleus_charge = 1UL;

        for (uint32_t i=0; i<nucleus->rank_nucleus_charge; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_nucleus_charge") != 0) || (j!=i)) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(nucleus->dims_nucleus_charge[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          size_nucleus_charge *= nucleus->dims_nucleus_charge[i];
        }
      } else if (strcmp(buffer, "rank_nucleus_coord") == 0) {

        rc = fscanf(f, "%u", &(nucleus->rank_nucleus_coord));
        if (rc != 1) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        if (nucleus->rank_nucleus_coord != 0) size_nucleus_coord = 1UL;

        for (uint32_t i=0; i<nucleus->rank_nucleus_coord; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_nucleus_coord") != 0) || (j!=i)) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(nucleus->dims_nucleus_coord[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          size_nucleus_coord *= nucleus->dims_nucleus_coord[i];
        }
      } else if (strcmp(buffer, "rank_nucleus_label") == 0) {

        rc = fscanf(f, "%u", &(nucleus->rank_nucleus_label));
        if (rc != 1) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        if (nucleus->rank_nucleus_label != 0) size_nucleus_label = 1UL;

        for (uint32_t i=0; i<nucleus->rank_nucleus_label; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_nucleus_label") != 0) || (j!=i)) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(nucleus->dims_nucleus_label[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          size_nucleus_label *= nucleus->dims_nucleus_label[i];
        }
      } else if (strcmp(buffer, "nucleus_charge") == 0) {

        /* Allocate arrays */
        nucleus->nucleus_charge = CALLOC(size_nucleus_charge, double);
        if (nucleus->nucleus_charge == NULL) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_nucleus_charge ; ++i) {
          rc = fscanf(f, "%lf", &(nucleus->nucleus_charge[i]));
          if (rc != 1) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "nucleus_coord") == 0) {

        /* Allocate arrays */
        nucleus->nucleus_coord = CALLOC(size_nucleus_coord, double);
        if (nucleus->nucleus_coord == NULL) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_nucleus_coord ; ++i) {
          rc = fscanf(f, "%lf", &(nucleus->nucleus_coord[i]));
          if (rc != 1) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "nucleus_label") == 0) {

        if (size_nucleus_label != 0) {
          /* Allocate arrays */
          nucleus->nucleus_label = CALLOC(size_nucleus_label, char*);
          if (nucleus->nucleus_label == NULL) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          /* WARNING: this tmp array allows to avoid allocation of space for each element of array of string
           * BUT it's size has to be number_of_str*max_len_str where max_len_str is somewhat arbitrary, e.g. 32.
           */
          char* tmp_nucleus_label;
          tmp_nucleus_label = CALLOC(size_nucleus_label*32, char);

          for (uint64_t i=0 ; i<size_nucleus_label ; ++i) {
            nucleus->nucleus_label[i] = tmp_nucleus_label;
            /* conventional fcanf with "%s" only return the string before the first space character
             * to read string with spaces use "%[^\n]" possible with space before or after, i.e. " %[^\n]"
             */
            rc = fscanf(f, " %1023[^\n]", buffer);
            if (rc != 1) {
              trexio_text_free_read_nucleus(buffer, f, file, nucleus);
              return NULL;
            }

            size_t tmp_nucleus_label_len = strlen(buffer);
            strncpy(tmp_nucleus_label, buffer, 32);
            tmp_nucleus_label[31] = '\0';
            tmp_nucleus_label += tmp_nucleus_label_len + 1;
          }
        }

      } else if (strcmp(buffer, "nucleus_num_isSet") == 0) {

        unsigned int nucleus_num_isSet;
        /* additional parameter nucleus_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(nucleus_num_isSet));
        nucleus->nucleus_num_isSet = (bool) nucleus_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        if (nucleus->nucleus_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "nucleus_num") != 0)) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(nucleus->nucleus_num));
          if (rc != 1) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "nucleus_repulsion_isSet") == 0) {

        unsigned int nucleus_repulsion_isSet;
        /* additional parameter nucleus_repulsion_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(nucleus_repulsion_isSet));
        nucleus->nucleus_repulsion_isSet = (bool) nucleus_repulsion_isSet;
        if (rc != 1) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        if (nucleus->nucleus_repulsion_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "nucleus_repulsion") != 0)) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          rc = fscanf(f, "%lf", &(nucleus->nucleus_repulsion));
          if (rc != 1) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "len_nucleus_point_group") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(nucleus->len_nucleus_point_group));
        if (rc != 1) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "nucleus_point_group") != 0)) {
          trexio_text_free_read_nucleus(buffer, f, file, nucleus);
          return NULL;
        }

        if (nucleus->len_nucleus_point_group != 0) {

          nucleus->nucleus_point_group = CALLOC(nucleus->len_nucleus_point_group, char);
          if (nucleus->nucleus_point_group == NULL) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_nucleus(buffer, f, file, nucleus);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(nucleus->nucleus_point_group, buffer, nucleus->len_nucleus_point_group);
          nucleus->nucleus_point_group[nucleus->len_nucleus_point_group-1] = '\0';

        }
      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->nucleus = nucleus;
  return nucleus;
}

cell_t*
trexio_text_read_cell (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->cell != NULL) {
    return file->cell;
  }

  /* Allocate the data structure */
  cell_t* cell = MALLOC(cell_t);
  if (cell == NULL) return NULL;

  memset(cell,0,sizeof(cell_t));

  /* Build the file name */
  const char cell_file_name[] = "/cell.txt";

  strncpy (cell->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  cell->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (cell->file_name, cell_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(cell_file_name));

  if (cell->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(cell);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(cell->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(cell);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_cell_a = 0;
    uint64_t size_cell_b = 0;
    uint64_t size_cell_c = 0;
    uint64_t size_cell_g_a = 0;
    uint64_t size_cell_g_b = 0;
    uint64_t size_cell_g_c = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_cell_a") == 0) {

        rc = fscanf(f, "%u", &(cell->rank_cell_a));
        if (rc != 1) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        if (cell->rank_cell_a != 0) size_cell_a = 1UL;

        for (uint32_t i=0; i<cell->rank_cell_a; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_cell_a") != 0) || (j!=i)) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(cell->dims_cell_a[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          size_cell_a *= cell->dims_cell_a[i];
        }
      } else if (strcmp(buffer, "rank_cell_b") == 0) {

        rc = fscanf(f, "%u", &(cell->rank_cell_b));
        if (rc != 1) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        if (cell->rank_cell_b != 0) size_cell_b = 1UL;

        for (uint32_t i=0; i<cell->rank_cell_b; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_cell_b") != 0) || (j!=i)) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(cell->dims_cell_b[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          size_cell_b *= cell->dims_cell_b[i];
        }
      } else if (strcmp(buffer, "rank_cell_c") == 0) {

        rc = fscanf(f, "%u", &(cell->rank_cell_c));
        if (rc != 1) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        if (cell->rank_cell_c != 0) size_cell_c = 1UL;

        for (uint32_t i=0; i<cell->rank_cell_c; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_cell_c") != 0) || (j!=i)) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(cell->dims_cell_c[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          size_cell_c *= cell->dims_cell_c[i];
        }
      } else if (strcmp(buffer, "rank_cell_g_a") == 0) {

        rc = fscanf(f, "%u", &(cell->rank_cell_g_a));
        if (rc != 1) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        if (cell->rank_cell_g_a != 0) size_cell_g_a = 1UL;

        for (uint32_t i=0; i<cell->rank_cell_g_a; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_cell_g_a") != 0) || (j!=i)) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(cell->dims_cell_g_a[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          size_cell_g_a *= cell->dims_cell_g_a[i];
        }
      } else if (strcmp(buffer, "rank_cell_g_b") == 0) {

        rc = fscanf(f, "%u", &(cell->rank_cell_g_b));
        if (rc != 1) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        if (cell->rank_cell_g_b != 0) size_cell_g_b = 1UL;

        for (uint32_t i=0; i<cell->rank_cell_g_b; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_cell_g_b") != 0) || (j!=i)) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(cell->dims_cell_g_b[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          size_cell_g_b *= cell->dims_cell_g_b[i];
        }
      } else if (strcmp(buffer, "rank_cell_g_c") == 0) {

        rc = fscanf(f, "%u", &(cell->rank_cell_g_c));
        if (rc != 1) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        if (cell->rank_cell_g_c != 0) size_cell_g_c = 1UL;

        for (uint32_t i=0; i<cell->rank_cell_g_c; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_cell_g_c") != 0) || (j!=i)) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(cell->dims_cell_g_c[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          size_cell_g_c *= cell->dims_cell_g_c[i];
        }
      } else if (strcmp(buffer, "cell_a") == 0) {

        /* Allocate arrays */
        cell->cell_a = CALLOC(size_cell_a, double);
        if (cell->cell_a == NULL) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_cell_a ; ++i) {
          rc = fscanf(f, "%lf", &(cell->cell_a[i]));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "cell_b") == 0) {

        /* Allocate arrays */
        cell->cell_b = CALLOC(size_cell_b, double);
        if (cell->cell_b == NULL) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_cell_b ; ++i) {
          rc = fscanf(f, "%lf", &(cell->cell_b[i]));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "cell_c") == 0) {

        /* Allocate arrays */
        cell->cell_c = CALLOC(size_cell_c, double);
        if (cell->cell_c == NULL) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_cell_c ; ++i) {
          rc = fscanf(f, "%lf", &(cell->cell_c[i]));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "cell_g_a") == 0) {

        /* Allocate arrays */
        cell->cell_g_a = CALLOC(size_cell_g_a, double);
        if (cell->cell_g_a == NULL) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_cell_g_a ; ++i) {
          rc = fscanf(f, "%lf", &(cell->cell_g_a[i]));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "cell_g_b") == 0) {

        /* Allocate arrays */
        cell->cell_g_b = CALLOC(size_cell_g_b, double);
        if (cell->cell_g_b == NULL) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_cell_g_b ; ++i) {
          rc = fscanf(f, "%lf", &(cell->cell_g_b[i]));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "cell_g_c") == 0) {

        /* Allocate arrays */
        cell->cell_g_c = CALLOC(size_cell_g_c, double);
        if (cell->cell_g_c == NULL) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_cell_g_c ; ++i) {
          rc = fscanf(f, "%lf", &(cell->cell_g_c[i]));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "cell_two_pi_isSet") == 0) {

        unsigned int cell_two_pi_isSet;
        /* additional parameter cell_two_pi_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(cell_two_pi_isSet));
        cell->cell_two_pi_isSet = (bool) cell_two_pi_isSet;
        if (rc != 1) {
          trexio_text_free_read_cell(buffer, f, file, cell);
          return NULL;
        }

        if (cell->cell_two_pi_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "cell_two_pi") != 0)) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(cell->cell_two_pi));
          if (rc != 1) {
            trexio_text_free_read_cell(buffer, f, file, cell);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->cell = cell;
  return cell;
}

pbc_t*
trexio_text_read_pbc (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->pbc != NULL) {
    return file->pbc;
  }

  /* Allocate the data structure */
  pbc_t* pbc = MALLOC(pbc_t);
  if (pbc == NULL) return NULL;

  memset(pbc,0,sizeof(pbc_t));

  /* Build the file name */
  const char pbc_file_name[] = "/pbc.txt";

  strncpy (pbc->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  pbc->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (pbc->file_name, pbc_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(pbc_file_name));

  if (pbc->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(pbc);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(pbc->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(pbc);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_pbc_k_point = 0;
    uint64_t size_pbc_k_point_weight = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_pbc_k_point") == 0) {

        rc = fscanf(f, "%u", &(pbc->rank_pbc_k_point));
        if (rc != 1) {
          trexio_text_free_read_pbc(buffer, f, file, pbc);
          return NULL;
        }

        if (pbc->rank_pbc_k_point != 0) size_pbc_k_point = 1UL;

        for (uint32_t i=0; i<pbc->rank_pbc_k_point; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_pbc_k_point") != 0) || (j!=i)) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(pbc->dims_pbc_k_point[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

          size_pbc_k_point *= pbc->dims_pbc_k_point[i];
        }
      } else if (strcmp(buffer, "rank_pbc_k_point_weight") == 0) {

        rc = fscanf(f, "%u", &(pbc->rank_pbc_k_point_weight));
        if (rc != 1) {
          trexio_text_free_read_pbc(buffer, f, file, pbc);
          return NULL;
        }

        if (pbc->rank_pbc_k_point_weight != 0) size_pbc_k_point_weight = 1UL;

        for (uint32_t i=0; i<pbc->rank_pbc_k_point_weight; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_pbc_k_point_weight") != 0) || (j!=i)) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(pbc->dims_pbc_k_point_weight[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

          size_pbc_k_point_weight *= pbc->dims_pbc_k_point_weight[i];
        }
      } else if (strcmp(buffer, "pbc_k_point") == 0) {

        /* Allocate arrays */
        pbc->pbc_k_point = CALLOC(size_pbc_k_point, double);
        if (pbc->pbc_k_point == NULL) {
          trexio_text_free_read_pbc(buffer, f, file, pbc);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_pbc_k_point ; ++i) {
          rc = fscanf(f, "%lf", &(pbc->pbc_k_point[i]));
          if (rc != 1) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "pbc_k_point_weight") == 0) {

        /* Allocate arrays */
        pbc->pbc_k_point_weight = CALLOC(size_pbc_k_point_weight, double);
        if (pbc->pbc_k_point_weight == NULL) {
          trexio_text_free_read_pbc(buffer, f, file, pbc);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_pbc_k_point_weight ; ++i) {
          rc = fscanf(f, "%lf", &(pbc->pbc_k_point_weight[i]));
          if (rc != 1) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "pbc_periodic_isSet") == 0) {

        unsigned int pbc_periodic_isSet;
        /* additional parameter pbc_periodic_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(pbc_periodic_isSet));
        pbc->pbc_periodic_isSet = (bool) pbc_periodic_isSet;
        if (rc != 1) {
          trexio_text_free_read_pbc(buffer, f, file, pbc);
          return NULL;
        }

        if (pbc->pbc_periodic_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "pbc_periodic") != 0)) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(pbc->pbc_periodic));
          if (rc != 1) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "pbc_k_point_num_isSet") == 0) {

        unsigned int pbc_k_point_num_isSet;
        /* additional parameter pbc_k_point_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(pbc_k_point_num_isSet));
        pbc->pbc_k_point_num_isSet = (bool) pbc_k_point_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_pbc(buffer, f, file, pbc);
          return NULL;
        }

        if (pbc->pbc_k_point_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "pbc_k_point_num") != 0)) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(pbc->pbc_k_point_num));
          if (rc != 1) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "pbc_madelung_isSet") == 0) {

        unsigned int pbc_madelung_isSet;
        /* additional parameter pbc_madelung_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(pbc_madelung_isSet));
        pbc->pbc_madelung_isSet = (bool) pbc_madelung_isSet;
        if (rc != 1) {
          trexio_text_free_read_pbc(buffer, f, file, pbc);
          return NULL;
        }

        if (pbc->pbc_madelung_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "pbc_madelung") != 0)) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

          rc = fscanf(f, "%lf", &(pbc->pbc_madelung));
          if (rc != 1) {
            trexio_text_free_read_pbc(buffer, f, file, pbc);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->pbc = pbc;
  return pbc;
}

electron_t*
trexio_text_read_electron (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->electron != NULL) {
    return file->electron;
  }

  /* Allocate the data structure */
  electron_t* electron = MALLOC(electron_t);
  if (electron == NULL) return NULL;

  memset(electron,0,sizeof(electron_t));

  /* Build the file name */
  const char electron_file_name[] = "/electron.txt";

  strncpy (electron->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  electron->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (electron->file_name, electron_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(electron_file_name));

  if (electron->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(electron);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(electron->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(electron);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "electron_num_isSet") == 0) {

        unsigned int electron_num_isSet;
        /* additional parameter electron_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(electron_num_isSet));
        electron->electron_num_isSet = (bool) electron_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_electron(buffer, f, file, electron);
          return NULL;
        }

        if (electron->electron_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "electron_num") != 0)) {
            trexio_text_free_read_electron(buffer, f, file, electron);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(electron->electron_num));
          if (rc != 1) {
            trexio_text_free_read_electron(buffer, f, file, electron);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "electron_up_num_isSet") == 0) {

        unsigned int electron_up_num_isSet;
        /* additional parameter electron_up_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(electron_up_num_isSet));
        electron->electron_up_num_isSet = (bool) electron_up_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_electron(buffer, f, file, electron);
          return NULL;
        }

        if (electron->electron_up_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "electron_up_num") != 0)) {
            trexio_text_free_read_electron(buffer, f, file, electron);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(electron->electron_up_num));
          if (rc != 1) {
            trexio_text_free_read_electron(buffer, f, file, electron);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "electron_dn_num_isSet") == 0) {

        unsigned int electron_dn_num_isSet;
        /* additional parameter electron_dn_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(electron_dn_num_isSet));
        electron->electron_dn_num_isSet = (bool) electron_dn_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_electron(buffer, f, file, electron);
          return NULL;
        }

        if (electron->electron_dn_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "electron_dn_num") != 0)) {
            trexio_text_free_read_electron(buffer, f, file, electron);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(electron->electron_dn_num));
          if (rc != 1) {
            trexio_text_free_read_electron(buffer, f, file, electron);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->electron = electron;
  return electron;
}

state_t*
trexio_text_read_state (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->state != NULL) {
    return file->state;
  }

  /* Allocate the data structure */
  state_t* state = MALLOC(state_t);
  if (state == NULL) return NULL;

  memset(state,0,sizeof(state_t));

  /* Build the file name */
  const char state_file_name[] = "/state.txt";

  strncpy (state->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  state->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (state->file_name, state_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(state_file_name));

  if (state->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(state);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(state->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(state);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_state_label = 0;
    uint64_t size_state_file_name = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_state_label") == 0) {

        rc = fscanf(f, "%u", &(state->rank_state_label));
        if (rc != 1) {
          trexio_text_free_read_state(buffer, f, file, state);
          return NULL;
        }

        if (state->rank_state_label != 0) size_state_label = 1UL;

        for (uint32_t i=0; i<state->rank_state_label; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_state_label") != 0) || (j!=i)) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(state->dims_state_label[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          size_state_label *= state->dims_state_label[i];
        }
      } else if (strcmp(buffer, "rank_state_file_name") == 0) {

        rc = fscanf(f, "%u", &(state->rank_state_file_name));
        if (rc != 1) {
          trexio_text_free_read_state(buffer, f, file, state);
          return NULL;
        }

        if (state->rank_state_file_name != 0) size_state_file_name = 1UL;

        for (uint32_t i=0; i<state->rank_state_file_name; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_state_file_name") != 0) || (j!=i)) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(state->dims_state_file_name[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          size_state_file_name *= state->dims_state_file_name[i];
        }
      } else if (strcmp(buffer, "state_label") == 0) {

        if (size_state_label != 0) {
          /* Allocate arrays */
          state->state_label = CALLOC(size_state_label, char*);
          if (state->state_label == NULL) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          /* WARNING: this tmp array allows to avoid allocation of space for each element of array of string
           * BUT it's size has to be number_of_str*max_len_str where max_len_str is somewhat arbitrary, e.g. 32.
           */
          char* tmp_state_label;
          tmp_state_label = CALLOC(size_state_label*32, char);

          for (uint64_t i=0 ; i<size_state_label ; ++i) {
            state->state_label[i] = tmp_state_label;
            /* conventional fcanf with "%s" only return the string before the first space character
             * to read string with spaces use "%[^\n]" possible with space before or after, i.e. " %[^\n]"
             */
            rc = fscanf(f, " %1023[^\n]", buffer);
            if (rc != 1) {
              trexio_text_free_read_state(buffer, f, file, state);
              return NULL;
            }

            size_t tmp_state_label_len = strlen(buffer);
            strncpy(tmp_state_label, buffer, 32);
            tmp_state_label[31] = '\0';
            tmp_state_label += tmp_state_label_len + 1;
          }
        }

      } else if (strcmp(buffer, "state_file_name") == 0) {

        if (size_state_file_name != 0) {
          /* Allocate arrays */
          state->state_file_name = CALLOC(size_state_file_name, char*);
          if (state->state_file_name == NULL) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          /* WARNING: this tmp array allows to avoid allocation of space for each element of array of string
           * BUT it's size has to be number_of_str*max_len_str where max_len_str is somewhat arbitrary, e.g. 32.
           */
          char* tmp_state_file_name;
          tmp_state_file_name = CALLOC(size_state_file_name*32, char);

          for (uint64_t i=0 ; i<size_state_file_name ; ++i) {
            state->state_file_name[i] = tmp_state_file_name;
            /* conventional fcanf with "%s" only return the string before the first space character
             * to read string with spaces use "%[^\n]" possible with space before or after, i.e. " %[^\n]"
             */
            rc = fscanf(f, " %1023[^\n]", buffer);
            if (rc != 1) {
              trexio_text_free_read_state(buffer, f, file, state);
              return NULL;
            }

            size_t tmp_state_file_name_len = strlen(buffer);
            strncpy(tmp_state_file_name, buffer, 32);
            tmp_state_file_name[31] = '\0';
            tmp_state_file_name += tmp_state_file_name_len + 1;
          }
        }

      } else if (strcmp(buffer, "state_num_isSet") == 0) {

        unsigned int state_num_isSet;
        /* additional parameter state_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(state_num_isSet));
        state->state_num_isSet = (bool) state_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_state(buffer, f, file, state);
          return NULL;
        }

        if (state->state_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "state_num") != 0)) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(state->state_num));
          if (rc != 1) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "state_id_isSet") == 0) {

        unsigned int state_id_isSet;
        /* additional parameter state_id_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(state_id_isSet));
        state->state_id_isSet = (bool) state_id_isSet;
        if (rc != 1) {
          trexio_text_free_read_state(buffer, f, file, state);
          return NULL;
        }

        if (state->state_id_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "state_id") != 0)) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(state->state_id));
          if (rc != 1) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "state_energy_isSet") == 0) {

        unsigned int state_energy_isSet;
        /* additional parameter state_energy_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(state_energy_isSet));
        state->state_energy_isSet = (bool) state_energy_isSet;
        if (rc != 1) {
          trexio_text_free_read_state(buffer, f, file, state);
          return NULL;
        }

        if (state->state_energy_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "state_energy") != 0)) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          rc = fscanf(f, "%lf", &(state->state_energy));
          if (rc != 1) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "len_state_current_label") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(state->len_state_current_label));
        if (rc != 1) {
          trexio_text_free_read_state(buffer, f, file, state);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "state_current_label") != 0)) {
          trexio_text_free_read_state(buffer, f, file, state);
          return NULL;
        }

        if (state->len_state_current_label != 0) {

          state->state_current_label = CALLOC(state->len_state_current_label, char);
          if (state->state_current_label == NULL) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_state(buffer, f, file, state);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(state->state_current_label, buffer, state->len_state_current_label);
          state->state_current_label[state->len_state_current_label-1] = '\0';

        }
      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->state = state;
  return state;
}

basis_t*
trexio_text_read_basis (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->basis != NULL) {
    return file->basis;
  }

  /* Allocate the data structure */
  basis_t* basis = MALLOC(basis_t);
  if (basis == NULL) return NULL;

  memset(basis,0,sizeof(basis_t));

  /* Build the file name */
  const char basis_file_name[] = "/basis.txt";

  strncpy (basis->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  basis->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (basis->file_name, basis_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(basis_file_name));

  if (basis->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(basis);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(basis->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(basis);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_basis_nucleus_index = 0;
    uint64_t size_basis_shell_ang_mom = 0;
    uint64_t size_basis_shell_factor = 0;
    uint64_t size_basis_r_power = 0;
    uint64_t size_basis_nao_grid_start = 0;
    uint64_t size_basis_nao_grid_size = 0;
    uint64_t size_basis_shell_index = 0;
    uint64_t size_basis_exponent = 0;
    uint64_t size_basis_exponent_im = 0;
    uint64_t size_basis_coefficient = 0;
    uint64_t size_basis_coefficient_im = 0;
    uint64_t size_basis_oscillation_arg = 0;
    uint64_t size_basis_prim_factor = 0;
    uint64_t size_basis_nao_grid_radius = 0;
    uint64_t size_basis_nao_grid_phi = 0;
    uint64_t size_basis_nao_grid_grad = 0;
    uint64_t size_basis_nao_grid_lap = 0;
    uint64_t size_basis_interpolator_phi = 0;
    uint64_t size_basis_interpolator_grad = 0;
    uint64_t size_basis_interpolator_lap = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_basis_nucleus_index") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_nucleus_index));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_nucleus_index != 0) size_basis_nucleus_index = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_nucleus_index; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_nucleus_index") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_nucleus_index[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_nucleus_index *= basis->dims_basis_nucleus_index[i];
        }
      } else if (strcmp(buffer, "rank_basis_shell_ang_mom") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_shell_ang_mom));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_shell_ang_mom != 0) size_basis_shell_ang_mom = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_shell_ang_mom; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_shell_ang_mom") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_shell_ang_mom[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_shell_ang_mom *= basis->dims_basis_shell_ang_mom[i];
        }
      } else if (strcmp(buffer, "rank_basis_shell_factor") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_shell_factor));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_shell_factor != 0) size_basis_shell_factor = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_shell_factor; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_shell_factor") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_shell_factor[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_shell_factor *= basis->dims_basis_shell_factor[i];
        }
      } else if (strcmp(buffer, "rank_basis_r_power") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_r_power));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_r_power != 0) size_basis_r_power = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_r_power; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_r_power") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_r_power[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_r_power *= basis->dims_basis_r_power[i];
        }
      } else if (strcmp(buffer, "rank_basis_nao_grid_start") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_nao_grid_start));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_nao_grid_start != 0) size_basis_nao_grid_start = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_nao_grid_start; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_nao_grid_start") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_nao_grid_start[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_nao_grid_start *= basis->dims_basis_nao_grid_start[i];
        }
      } else if (strcmp(buffer, "rank_basis_nao_grid_size") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_nao_grid_size));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_nao_grid_size != 0) size_basis_nao_grid_size = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_nao_grid_size; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_nao_grid_size") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_nao_grid_size[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_nao_grid_size *= basis->dims_basis_nao_grid_size[i];
        }
      } else if (strcmp(buffer, "rank_basis_shell_index") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_shell_index));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_shell_index != 0) size_basis_shell_index = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_shell_index; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_shell_index") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_shell_index[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_shell_index *= basis->dims_basis_shell_index[i];
        }
      } else if (strcmp(buffer, "rank_basis_exponent") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_exponent));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_exponent != 0) size_basis_exponent = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_exponent; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_exponent") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_exponent[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_exponent *= basis->dims_basis_exponent[i];
        }
      } else if (strcmp(buffer, "rank_basis_exponent_im") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_exponent_im));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_exponent_im != 0) size_basis_exponent_im = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_exponent_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_exponent_im") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_exponent_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_exponent_im *= basis->dims_basis_exponent_im[i];
        }
      } else if (strcmp(buffer, "rank_basis_coefficient") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_coefficient));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_coefficient != 0) size_basis_coefficient = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_coefficient; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_coefficient") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_coefficient[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_coefficient *= basis->dims_basis_coefficient[i];
        }
      } else if (strcmp(buffer, "rank_basis_coefficient_im") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_coefficient_im));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_coefficient_im != 0) size_basis_coefficient_im = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_coefficient_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_coefficient_im") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_coefficient_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_coefficient_im *= basis->dims_basis_coefficient_im[i];
        }
      } else if (strcmp(buffer, "rank_basis_oscillation_arg") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_oscillation_arg));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_oscillation_arg != 0) size_basis_oscillation_arg = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_oscillation_arg; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_oscillation_arg") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_oscillation_arg[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_oscillation_arg *= basis->dims_basis_oscillation_arg[i];
        }
      } else if (strcmp(buffer, "rank_basis_prim_factor") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_prim_factor));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_prim_factor != 0) size_basis_prim_factor = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_prim_factor; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_prim_factor") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_prim_factor[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_prim_factor *= basis->dims_basis_prim_factor[i];
        }
      } else if (strcmp(buffer, "rank_basis_nao_grid_radius") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_nao_grid_radius));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_nao_grid_radius != 0) size_basis_nao_grid_radius = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_nao_grid_radius; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_nao_grid_radius") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_nao_grid_radius[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_nao_grid_radius *= basis->dims_basis_nao_grid_radius[i];
        }
      } else if (strcmp(buffer, "rank_basis_nao_grid_phi") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_nao_grid_phi));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_nao_grid_phi != 0) size_basis_nao_grid_phi = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_nao_grid_phi; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_nao_grid_phi") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_nao_grid_phi[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_nao_grid_phi *= basis->dims_basis_nao_grid_phi[i];
        }
      } else if (strcmp(buffer, "rank_basis_nao_grid_grad") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_nao_grid_grad));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_nao_grid_grad != 0) size_basis_nao_grid_grad = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_nao_grid_grad; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_nao_grid_grad") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_nao_grid_grad[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_nao_grid_grad *= basis->dims_basis_nao_grid_grad[i];
        }
      } else if (strcmp(buffer, "rank_basis_nao_grid_lap") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_nao_grid_lap));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_nao_grid_lap != 0) size_basis_nao_grid_lap = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_nao_grid_lap; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_nao_grid_lap") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_nao_grid_lap[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_nao_grid_lap *= basis->dims_basis_nao_grid_lap[i];
        }
      } else if (strcmp(buffer, "rank_basis_interpolator_phi") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_interpolator_phi));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_interpolator_phi != 0) size_basis_interpolator_phi = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_interpolator_phi; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_interpolator_phi") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_interpolator_phi[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_interpolator_phi *= basis->dims_basis_interpolator_phi[i];
        }
      } else if (strcmp(buffer, "rank_basis_interpolator_grad") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_interpolator_grad));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_interpolator_grad != 0) size_basis_interpolator_grad = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_interpolator_grad; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_interpolator_grad") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_interpolator_grad[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_interpolator_grad *= basis->dims_basis_interpolator_grad[i];
        }
      } else if (strcmp(buffer, "rank_basis_interpolator_lap") == 0) {

        rc = fscanf(f, "%u", &(basis->rank_basis_interpolator_lap));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->rank_basis_interpolator_lap != 0) size_basis_interpolator_lap = 1UL;

        for (uint32_t i=0; i<basis->rank_basis_interpolator_lap; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_basis_interpolator_lap") != 0) || (j!=i)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(basis->dims_basis_interpolator_lap[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          size_basis_interpolator_lap *= basis->dims_basis_interpolator_lap[i];
        }
      } else if (strcmp(buffer, "basis_nucleus_index") == 0) {

        /* Allocate arrays */
        basis->basis_nucleus_index = CALLOC(size_basis_nucleus_index, int64_t);
        if (basis->basis_nucleus_index == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_nucleus_index ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_nucleus_index[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_shell_ang_mom") == 0) {

        /* Allocate arrays */
        basis->basis_shell_ang_mom = CALLOC(size_basis_shell_ang_mom, int64_t);
        if (basis->basis_shell_ang_mom == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_shell_ang_mom ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_shell_ang_mom[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_shell_factor") == 0) {

        /* Allocate arrays */
        basis->basis_shell_factor = CALLOC(size_basis_shell_factor, double);
        if (basis->basis_shell_factor == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_shell_factor ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_shell_factor[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_r_power") == 0) {

        /* Allocate arrays */
        basis->basis_r_power = CALLOC(size_basis_r_power, int64_t);
        if (basis->basis_r_power == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_r_power ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_r_power[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_nao_grid_start") == 0) {

        /* Allocate arrays */
        basis->basis_nao_grid_start = CALLOC(size_basis_nao_grid_start, int64_t);
        if (basis->basis_nao_grid_start == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_nao_grid_start ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_nao_grid_start[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_nao_grid_size") == 0) {

        /* Allocate arrays */
        basis->basis_nao_grid_size = CALLOC(size_basis_nao_grid_size, int64_t);
        if (basis->basis_nao_grid_size == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_nao_grid_size ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_nao_grid_size[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_shell_index") == 0) {

        /* Allocate arrays */
        basis->basis_shell_index = CALLOC(size_basis_shell_index, int64_t);
        if (basis->basis_shell_index == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_shell_index ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_shell_index[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_exponent") == 0) {

        /* Allocate arrays */
        basis->basis_exponent = CALLOC(size_basis_exponent, double);
        if (basis->basis_exponent == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_exponent ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_exponent[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_exponent_im") == 0) {

        /* Allocate arrays */
        basis->basis_exponent_im = CALLOC(size_basis_exponent_im, double);
        if (basis->basis_exponent_im == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_exponent_im ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_exponent_im[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_coefficient") == 0) {

        /* Allocate arrays */
        basis->basis_coefficient = CALLOC(size_basis_coefficient, double);
        if (basis->basis_coefficient == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_coefficient ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_coefficient[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_coefficient_im") == 0) {

        /* Allocate arrays */
        basis->basis_coefficient_im = CALLOC(size_basis_coefficient_im, double);
        if (basis->basis_coefficient_im == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_coefficient_im ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_coefficient_im[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_oscillation_arg") == 0) {

        /* Allocate arrays */
        basis->basis_oscillation_arg = CALLOC(size_basis_oscillation_arg, double);
        if (basis->basis_oscillation_arg == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_oscillation_arg ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_oscillation_arg[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_prim_factor") == 0) {

        /* Allocate arrays */
        basis->basis_prim_factor = CALLOC(size_basis_prim_factor, double);
        if (basis->basis_prim_factor == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_prim_factor ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_prim_factor[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_nao_grid_radius") == 0) {

        /* Allocate arrays */
        basis->basis_nao_grid_radius = CALLOC(size_basis_nao_grid_radius, double);
        if (basis->basis_nao_grid_radius == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_nao_grid_radius ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_nao_grid_radius[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_nao_grid_phi") == 0) {

        /* Allocate arrays */
        basis->basis_nao_grid_phi = CALLOC(size_basis_nao_grid_phi, double);
        if (basis->basis_nao_grid_phi == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_nao_grid_phi ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_nao_grid_phi[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_nao_grid_grad") == 0) {

        /* Allocate arrays */
        basis->basis_nao_grid_grad = CALLOC(size_basis_nao_grid_grad, double);
        if (basis->basis_nao_grid_grad == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_nao_grid_grad ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_nao_grid_grad[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_nao_grid_lap") == 0) {

        /* Allocate arrays */
        basis->basis_nao_grid_lap = CALLOC(size_basis_nao_grid_lap, double);
        if (basis->basis_nao_grid_lap == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_nao_grid_lap ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_nao_grid_lap[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_interpolator_phi") == 0) {

        /* Allocate arrays */
        basis->basis_interpolator_phi = CALLOC(size_basis_interpolator_phi, double);
        if (basis->basis_interpolator_phi == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_interpolator_phi ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_interpolator_phi[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_interpolator_grad") == 0) {

        /* Allocate arrays */
        basis->basis_interpolator_grad = CALLOC(size_basis_interpolator_grad, double);
        if (basis->basis_interpolator_grad == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_interpolator_grad ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_interpolator_grad[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_interpolator_lap") == 0) {

        /* Allocate arrays */
        basis->basis_interpolator_lap = CALLOC(size_basis_interpolator_lap, double);
        if (basis->basis_interpolator_lap == NULL) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_basis_interpolator_lap ; ++i) {
          rc = fscanf(f, "%lf", &(basis->basis_interpolator_lap[i]));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "basis_prim_num_isSet") == 0) {

        unsigned int basis_prim_num_isSet;
        /* additional parameter basis_prim_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(basis_prim_num_isSet));
        basis->basis_prim_num_isSet = (bool) basis_prim_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->basis_prim_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "basis_prim_num") != 0)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_prim_num));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "basis_shell_num_isSet") == 0) {

        unsigned int basis_shell_num_isSet;
        /* additional parameter basis_shell_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(basis_shell_num_isSet));
        basis->basis_shell_num_isSet = (bool) basis_shell_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->basis_shell_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "basis_shell_num") != 0)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_shell_num));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "basis_nao_grid_num_isSet") == 0) {

        unsigned int basis_nao_grid_num_isSet;
        /* additional parameter basis_nao_grid_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(basis_nao_grid_num_isSet));
        basis->basis_nao_grid_num_isSet = (bool) basis_nao_grid_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->basis_nao_grid_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "basis_nao_grid_num") != 0)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_nao_grid_num));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "basis_interp_coeff_cnt_isSet") == 0) {

        unsigned int basis_interp_coeff_cnt_isSet;
        /* additional parameter basis_interp_coeff_cnt_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(basis_interp_coeff_cnt_isSet));
        basis->basis_interp_coeff_cnt_isSet = (bool) basis_interp_coeff_cnt_isSet;
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->basis_interp_coeff_cnt_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "basis_interp_coeff_cnt") != 0)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(basis->basis_interp_coeff_cnt));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "basis_e_cut_isSet") == 0) {

        unsigned int basis_e_cut_isSet;
        /* additional parameter basis_e_cut_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(basis_e_cut_isSet));
        basis->basis_e_cut_isSet = (bool) basis_e_cut_isSet;
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->basis_e_cut_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "basis_e_cut") != 0)) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, "%lf", &(basis->basis_e_cut));
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "len_basis_type") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(basis->len_basis_type));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "basis_type") != 0)) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->len_basis_type != 0) {

          basis->basis_type = CALLOC(basis->len_basis_type, char);
          if (basis->basis_type == NULL) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(basis->basis_type, buffer, basis->len_basis_type);
          basis->basis_type[basis->len_basis_type-1] = '\0';

        }
      } else if (strcmp(buffer, "len_basis_oscillation_kind") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(basis->len_basis_oscillation_kind));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "basis_oscillation_kind") != 0)) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->len_basis_oscillation_kind != 0) {

          basis->basis_oscillation_kind = CALLOC(basis->len_basis_oscillation_kind, char);
          if (basis->basis_oscillation_kind == NULL) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(basis->basis_oscillation_kind, buffer, basis->len_basis_oscillation_kind);
          basis->basis_oscillation_kind[basis->len_basis_oscillation_kind-1] = '\0';

        }
      } else if (strcmp(buffer, "len_basis_interpolator_kind") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(basis->len_basis_interpolator_kind));
        if (rc != 1) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "basis_interpolator_kind") != 0)) {
          trexio_text_free_read_basis(buffer, f, file, basis);
          return NULL;
        }

        if (basis->len_basis_interpolator_kind != 0) {

          basis->basis_interpolator_kind = CALLOC(basis->len_basis_interpolator_kind, char);
          if (basis->basis_interpolator_kind == NULL) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_basis(buffer, f, file, basis);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(basis->basis_interpolator_kind, buffer, basis->len_basis_interpolator_kind);
          basis->basis_interpolator_kind[basis->len_basis_interpolator_kind-1] = '\0';

        }
      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->basis = basis;
  return basis;
}

ecp_t*
trexio_text_read_ecp (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->ecp != NULL) {
    return file->ecp;
  }

  /* Allocate the data structure */
  ecp_t* ecp = MALLOC(ecp_t);
  if (ecp == NULL) return NULL;

  memset(ecp,0,sizeof(ecp_t));

  /* Build the file name */
  const char ecp_file_name[] = "/ecp.txt";

  strncpy (ecp->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  ecp->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (ecp->file_name, ecp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ecp_file_name));

  if (ecp->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(ecp);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(ecp->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(ecp);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_ecp_max_ang_mom_plus_1 = 0;
    uint64_t size_ecp_z_core = 0;
    uint64_t size_ecp_ang_mom = 0;
    uint64_t size_ecp_nucleus_index = 0;
    uint64_t size_ecp_exponent = 0;
    uint64_t size_ecp_coefficient = 0;
    uint64_t size_ecp_power = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_ecp_max_ang_mom_plus_1") == 0) {

        rc = fscanf(f, "%u", &(ecp->rank_ecp_max_ang_mom_plus_1));
        if (rc != 1) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        if (ecp->rank_ecp_max_ang_mom_plus_1 != 0) size_ecp_max_ang_mom_plus_1 = 1UL;

        for (uint32_t i=0; i<ecp->rank_ecp_max_ang_mom_plus_1; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ecp_max_ang_mom_plus_1") != 0) || (j!=i)) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ecp->dims_ecp_max_ang_mom_plus_1[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          size_ecp_max_ang_mom_plus_1 *= ecp->dims_ecp_max_ang_mom_plus_1[i];
        }
      } else if (strcmp(buffer, "rank_ecp_z_core") == 0) {

        rc = fscanf(f, "%u", &(ecp->rank_ecp_z_core));
        if (rc != 1) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        if (ecp->rank_ecp_z_core != 0) size_ecp_z_core = 1UL;

        for (uint32_t i=0; i<ecp->rank_ecp_z_core; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ecp_z_core") != 0) || (j!=i)) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ecp->dims_ecp_z_core[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          size_ecp_z_core *= ecp->dims_ecp_z_core[i];
        }
      } else if (strcmp(buffer, "rank_ecp_ang_mom") == 0) {

        rc = fscanf(f, "%u", &(ecp->rank_ecp_ang_mom));
        if (rc != 1) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        if (ecp->rank_ecp_ang_mom != 0) size_ecp_ang_mom = 1UL;

        for (uint32_t i=0; i<ecp->rank_ecp_ang_mom; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ecp_ang_mom") != 0) || (j!=i)) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ecp->dims_ecp_ang_mom[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          size_ecp_ang_mom *= ecp->dims_ecp_ang_mom[i];
        }
      } else if (strcmp(buffer, "rank_ecp_nucleus_index") == 0) {

        rc = fscanf(f, "%u", &(ecp->rank_ecp_nucleus_index));
        if (rc != 1) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        if (ecp->rank_ecp_nucleus_index != 0) size_ecp_nucleus_index = 1UL;

        for (uint32_t i=0; i<ecp->rank_ecp_nucleus_index; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ecp_nucleus_index") != 0) || (j!=i)) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ecp->dims_ecp_nucleus_index[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          size_ecp_nucleus_index *= ecp->dims_ecp_nucleus_index[i];
        }
      } else if (strcmp(buffer, "rank_ecp_exponent") == 0) {

        rc = fscanf(f, "%u", &(ecp->rank_ecp_exponent));
        if (rc != 1) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        if (ecp->rank_ecp_exponent != 0) size_ecp_exponent = 1UL;

        for (uint32_t i=0; i<ecp->rank_ecp_exponent; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ecp_exponent") != 0) || (j!=i)) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ecp->dims_ecp_exponent[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          size_ecp_exponent *= ecp->dims_ecp_exponent[i];
        }
      } else if (strcmp(buffer, "rank_ecp_coefficient") == 0) {

        rc = fscanf(f, "%u", &(ecp->rank_ecp_coefficient));
        if (rc != 1) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        if (ecp->rank_ecp_coefficient != 0) size_ecp_coefficient = 1UL;

        for (uint32_t i=0; i<ecp->rank_ecp_coefficient; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ecp_coefficient") != 0) || (j!=i)) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ecp->dims_ecp_coefficient[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          size_ecp_coefficient *= ecp->dims_ecp_coefficient[i];
        }
      } else if (strcmp(buffer, "rank_ecp_power") == 0) {

        rc = fscanf(f, "%u", &(ecp->rank_ecp_power));
        if (rc != 1) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        if (ecp->rank_ecp_power != 0) size_ecp_power = 1UL;

        for (uint32_t i=0; i<ecp->rank_ecp_power; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ecp_power") != 0) || (j!=i)) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ecp->dims_ecp_power[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          size_ecp_power *= ecp->dims_ecp_power[i];
        }
      } else if (strcmp(buffer, "ecp_max_ang_mom_plus_1") == 0) {

        /* Allocate arrays */
        ecp->ecp_max_ang_mom_plus_1 = CALLOC(size_ecp_max_ang_mom_plus_1, int64_t);
        if (ecp->ecp_max_ang_mom_plus_1 == NULL) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ecp_max_ang_mom_plus_1 ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(ecp->ecp_max_ang_mom_plus_1[i]));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ecp_z_core") == 0) {

        /* Allocate arrays */
        ecp->ecp_z_core = CALLOC(size_ecp_z_core, int64_t);
        if (ecp->ecp_z_core == NULL) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ecp_z_core ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(ecp->ecp_z_core[i]));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ecp_ang_mom") == 0) {

        /* Allocate arrays */
        ecp->ecp_ang_mom = CALLOC(size_ecp_ang_mom, int64_t);
        if (ecp->ecp_ang_mom == NULL) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ecp_ang_mom ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(ecp->ecp_ang_mom[i]));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ecp_nucleus_index") == 0) {

        /* Allocate arrays */
        ecp->ecp_nucleus_index = CALLOC(size_ecp_nucleus_index, int64_t);
        if (ecp->ecp_nucleus_index == NULL) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ecp_nucleus_index ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(ecp->ecp_nucleus_index[i]));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ecp_exponent") == 0) {

        /* Allocate arrays */
        ecp->ecp_exponent = CALLOC(size_ecp_exponent, double);
        if (ecp->ecp_exponent == NULL) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ecp_exponent ; ++i) {
          rc = fscanf(f, "%lf", &(ecp->ecp_exponent[i]));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ecp_coefficient") == 0) {

        /* Allocate arrays */
        ecp->ecp_coefficient = CALLOC(size_ecp_coefficient, double);
        if (ecp->ecp_coefficient == NULL) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ecp_coefficient ; ++i) {
          rc = fscanf(f, "%lf", &(ecp->ecp_coefficient[i]));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ecp_power") == 0) {

        /* Allocate arrays */
        ecp->ecp_power = CALLOC(size_ecp_power, int64_t);
        if (ecp->ecp_power == NULL) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ecp_power ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(ecp->ecp_power[i]));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ecp_num_isSet") == 0) {

        unsigned int ecp_num_isSet;
        /* additional parameter ecp_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(ecp_num_isSet));
        ecp->ecp_num_isSet = (bool) ecp_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_ecp(buffer, f, file, ecp);
          return NULL;
        }

        if (ecp->ecp_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "ecp_num") != 0)) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(ecp->ecp_num));
          if (rc != 1) {
            trexio_text_free_read_ecp(buffer, f, file, ecp);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->ecp = ecp;
  return ecp;
}

grid_t*
trexio_text_read_grid (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->grid != NULL) {
    return file->grid;
  }

  /* Allocate the data structure */
  grid_t* grid = MALLOC(grid_t);
  if (grid == NULL) return NULL;

  memset(grid,0,sizeof(grid_t));

  /* Build the file name */
  const char grid_file_name[] = "/grid.txt";

  strncpy (grid->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  grid->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (grid->file_name, grid_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(grid_file_name));

  if (grid->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(grid);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(grid->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(grid);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_grid_coord = 0;
    uint64_t size_grid_weight = 0;
    uint64_t size_grid_ang_coord = 0;
    uint64_t size_grid_ang_weight = 0;
    uint64_t size_grid_rad_coord = 0;
    uint64_t size_grid_rad_weight = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_grid_coord") == 0) {

        rc = fscanf(f, "%u", &(grid->rank_grid_coord));
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->rank_grid_coord != 0) size_grid_coord = 1UL;

        for (uint32_t i=0; i<grid->rank_grid_coord; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_grid_coord") != 0) || (j!=i)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(grid->dims_grid_coord[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          size_grid_coord *= grid->dims_grid_coord[i];
        }
      } else if (strcmp(buffer, "rank_grid_weight") == 0) {

        rc = fscanf(f, "%u", &(grid->rank_grid_weight));
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->rank_grid_weight != 0) size_grid_weight = 1UL;

        for (uint32_t i=0; i<grid->rank_grid_weight; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_grid_weight") != 0) || (j!=i)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(grid->dims_grid_weight[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          size_grid_weight *= grid->dims_grid_weight[i];
        }
      } else if (strcmp(buffer, "rank_grid_ang_coord") == 0) {

        rc = fscanf(f, "%u", &(grid->rank_grid_ang_coord));
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->rank_grid_ang_coord != 0) size_grid_ang_coord = 1UL;

        for (uint32_t i=0; i<grid->rank_grid_ang_coord; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_grid_ang_coord") != 0) || (j!=i)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(grid->dims_grid_ang_coord[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          size_grid_ang_coord *= grid->dims_grid_ang_coord[i];
        }
      } else if (strcmp(buffer, "rank_grid_ang_weight") == 0) {

        rc = fscanf(f, "%u", &(grid->rank_grid_ang_weight));
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->rank_grid_ang_weight != 0) size_grid_ang_weight = 1UL;

        for (uint32_t i=0; i<grid->rank_grid_ang_weight; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_grid_ang_weight") != 0) || (j!=i)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(grid->dims_grid_ang_weight[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          size_grid_ang_weight *= grid->dims_grid_ang_weight[i];
        }
      } else if (strcmp(buffer, "rank_grid_rad_coord") == 0) {

        rc = fscanf(f, "%u", &(grid->rank_grid_rad_coord));
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->rank_grid_rad_coord != 0) size_grid_rad_coord = 1UL;

        for (uint32_t i=0; i<grid->rank_grid_rad_coord; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_grid_rad_coord") != 0) || (j!=i)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(grid->dims_grid_rad_coord[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          size_grid_rad_coord *= grid->dims_grid_rad_coord[i];
        }
      } else if (strcmp(buffer, "rank_grid_rad_weight") == 0) {

        rc = fscanf(f, "%u", &(grid->rank_grid_rad_weight));
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->rank_grid_rad_weight != 0) size_grid_rad_weight = 1UL;

        for (uint32_t i=0; i<grid->rank_grid_rad_weight; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_grid_rad_weight") != 0) || (j!=i)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(grid->dims_grid_rad_weight[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          size_grid_rad_weight *= grid->dims_grid_rad_weight[i];
        }
      } else if (strcmp(buffer, "grid_coord") == 0) {

        /* Allocate arrays */
        grid->grid_coord = CALLOC(size_grid_coord, double);
        if (grid->grid_coord == NULL) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_grid_coord ; ++i) {
          rc = fscanf(f, "%lf", &(grid->grid_coord[i]));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "grid_weight") == 0) {

        /* Allocate arrays */
        grid->grid_weight = CALLOC(size_grid_weight, double);
        if (grid->grid_weight == NULL) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_grid_weight ; ++i) {
          rc = fscanf(f, "%lf", &(grid->grid_weight[i]));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "grid_ang_coord") == 0) {

        /* Allocate arrays */
        grid->grid_ang_coord = CALLOC(size_grid_ang_coord, double);
        if (grid->grid_ang_coord == NULL) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_grid_ang_coord ; ++i) {
          rc = fscanf(f, "%lf", &(grid->grid_ang_coord[i]));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "grid_ang_weight") == 0) {

        /* Allocate arrays */
        grid->grid_ang_weight = CALLOC(size_grid_ang_weight, double);
        if (grid->grid_ang_weight == NULL) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_grid_ang_weight ; ++i) {
          rc = fscanf(f, "%lf", &(grid->grid_ang_weight[i]));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "grid_rad_coord") == 0) {

        /* Allocate arrays */
        grid->grid_rad_coord = CALLOC(size_grid_rad_coord, double);
        if (grid->grid_rad_coord == NULL) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_grid_rad_coord ; ++i) {
          rc = fscanf(f, "%lf", &(grid->grid_rad_coord[i]));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "grid_rad_weight") == 0) {

        /* Allocate arrays */
        grid->grid_rad_weight = CALLOC(size_grid_rad_weight, double);
        if (grid->grid_rad_weight == NULL) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_grid_rad_weight ; ++i) {
          rc = fscanf(f, "%lf", &(grid->grid_rad_weight[i]));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "grid_rad_precision_isSet") == 0) {

        unsigned int grid_rad_precision_isSet;
        /* additional parameter grid_rad_precision_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(grid_rad_precision_isSet));
        grid->grid_rad_precision_isSet = (bool) grid_rad_precision_isSet;
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->grid_rad_precision_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "grid_rad_precision") != 0)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%lf", &(grid->grid_rad_precision));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "grid_num_isSet") == 0) {

        unsigned int grid_num_isSet;
        /* additional parameter grid_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(grid_num_isSet));
        grid->grid_num_isSet = (bool) grid_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->grid_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "grid_num") != 0)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(grid->grid_num));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "grid_max_ang_num_isSet") == 0) {

        unsigned int grid_max_ang_num_isSet;
        /* additional parameter grid_max_ang_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(grid_max_ang_num_isSet));
        grid->grid_max_ang_num_isSet = (bool) grid_max_ang_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->grid_max_ang_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "grid_max_ang_num") != 0)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(grid->grid_max_ang_num));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "grid_min_ang_num_isSet") == 0) {

        unsigned int grid_min_ang_num_isSet;
        /* additional parameter grid_min_ang_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(grid_min_ang_num_isSet));
        grid->grid_min_ang_num_isSet = (bool) grid_min_ang_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->grid_min_ang_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "grid_min_ang_num") != 0)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(grid->grid_min_ang_num));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "grid_ang_num_isSet") == 0) {

        unsigned int grid_ang_num_isSet;
        /* additional parameter grid_ang_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(grid_ang_num_isSet));
        grid->grid_ang_num_isSet = (bool) grid_ang_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->grid_ang_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "grid_ang_num") != 0)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(grid->grid_ang_num));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "grid_rad_num_isSet") == 0) {

        unsigned int grid_rad_num_isSet;
        /* additional parameter grid_rad_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(grid_rad_num_isSet));
        grid->grid_rad_num_isSet = (bool) grid_rad_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->grid_rad_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "grid_rad_num") != 0)) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(grid->grid_rad_num));
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "len_grid_description") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(grid->len_grid_description));
        if (rc != 1) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "grid_description") != 0)) {
          trexio_text_free_read_grid(buffer, f, file, grid);
          return NULL;
        }

        if (grid->len_grid_description != 0) {

          grid->grid_description = CALLOC(grid->len_grid_description, char);
          if (grid->grid_description == NULL) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_grid(buffer, f, file, grid);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(grid->grid_description, buffer, grid->len_grid_description);
          grid->grid_description[grid->len_grid_description-1] = '\0';

        }
      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->grid = grid;
  return grid;
}

ao_t*
trexio_text_read_ao (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->ao != NULL) {
    return file->ao;
  }

  /* Allocate the data structure */
  ao_t* ao = MALLOC(ao_t);
  if (ao == NULL) return NULL;

  memset(ao,0,sizeof(ao_t));

  /* Build the file name */
  const char ao_file_name[] = "/ao.txt";

  strncpy (ao->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  ao->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (ao->file_name, ao_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_file_name));

  if (ao->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(ao);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(ao->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(ao);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_ao_shell = 0;
    uint64_t size_ao_normalization = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_ao_shell") == 0) {

        rc = fscanf(f, "%u", &(ao->rank_ao_shell));
        if (rc != 1) {
          trexio_text_free_read_ao(buffer, f, file, ao);
          return NULL;
        }

        if (ao->rank_ao_shell != 0) size_ao_shell = 1UL;

        for (uint32_t i=0; i<ao->rank_ao_shell; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_shell") != 0) || (j!=i)) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao->dims_ao_shell[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }

          size_ao_shell *= ao->dims_ao_shell[i];
        }
      } else if (strcmp(buffer, "rank_ao_normalization") == 0) {

        rc = fscanf(f, "%u", &(ao->rank_ao_normalization));
        if (rc != 1) {
          trexio_text_free_read_ao(buffer, f, file, ao);
          return NULL;
        }

        if (ao->rank_ao_normalization != 0) size_ao_normalization = 1UL;

        for (uint32_t i=0; i<ao->rank_ao_normalization; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_normalization") != 0) || (j!=i)) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao->dims_ao_normalization[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }

          size_ao_normalization *= ao->dims_ao_normalization[i];
        }
      } else if (strcmp(buffer, "ao_shell") == 0) {

        /* Allocate arrays */
        ao->ao_shell = CALLOC(size_ao_shell, int64_t);
        if (ao->ao_shell == NULL) {
          trexio_text_free_read_ao(buffer, f, file, ao);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_shell ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(ao->ao_shell[i]));
          if (rc != 1) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_normalization") == 0) {

        /* Allocate arrays */
        ao->ao_normalization = CALLOC(size_ao_normalization, double);
        if (ao->ao_normalization == NULL) {
          trexio_text_free_read_ao(buffer, f, file, ao);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_normalization ; ++i) {
          rc = fscanf(f, "%lf", &(ao->ao_normalization[i]));
          if (rc != 1) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_cartesian_isSet") == 0) {

        unsigned int ao_cartesian_isSet;
        /* additional parameter ao_cartesian_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(ao_cartesian_isSet));
        ao->ao_cartesian_isSet = (bool) ao_cartesian_isSet;
        if (rc != 1) {
          trexio_text_free_read_ao(buffer, f, file, ao);
          return NULL;
        }

        if (ao->ao_cartesian_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "ao_cartesian") != 0)) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(ao->ao_cartesian));
          if (rc != 1) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "ao_num_isSet") == 0) {

        unsigned int ao_num_isSet;
        /* additional parameter ao_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(ao_num_isSet));
        ao->ao_num_isSet = (bool) ao_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_ao(buffer, f, file, ao);
          return NULL;
        }

        if (ao->ao_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "ao_num") != 0)) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(ao->ao_num));
          if (rc != 1) {
            trexio_text_free_read_ao(buffer, f, file, ao);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->ao = ao;
  return ao;
}

ao_1e_int_t*
trexio_text_read_ao_1e_int (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->ao_1e_int != NULL) {
    return file->ao_1e_int;
  }

  /* Allocate the data structure */
  ao_1e_int_t* ao_1e_int = MALLOC(ao_1e_int_t);
  if (ao_1e_int == NULL) return NULL;

  memset(ao_1e_int,0,sizeof(ao_1e_int_t));

  /* Build the file name */
  const char ao_1e_int_file_name[] = "/ao_1e_int.txt";

  strncpy (ao_1e_int->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  ao_1e_int->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (ao_1e_int->file_name, ao_1e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_1e_int_file_name));

  if (ao_1e_int->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(ao_1e_int);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(ao_1e_int->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(ao_1e_int);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_ao_1e_int_overlap = 0;
    uint64_t size_ao_1e_int_kinetic = 0;
    uint64_t size_ao_1e_int_potential_n_e = 0;
    uint64_t size_ao_1e_int_ecp = 0;
    uint64_t size_ao_1e_int_core_hamiltonian = 0;
    uint64_t size_ao_1e_int_overlap_im = 0;
    uint64_t size_ao_1e_int_kinetic_im = 0;
    uint64_t size_ao_1e_int_potential_n_e_im = 0;
    uint64_t size_ao_1e_int_ecp_im = 0;
    uint64_t size_ao_1e_int_core_hamiltonian_im = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_ao_1e_int_overlap") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_overlap));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_overlap != 0) size_ao_1e_int_overlap = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_overlap; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_overlap") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_overlap[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_overlap *= ao_1e_int->dims_ao_1e_int_overlap[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_kinetic") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_kinetic));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_kinetic != 0) size_ao_1e_int_kinetic = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_kinetic; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_kinetic") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_kinetic[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_kinetic *= ao_1e_int->dims_ao_1e_int_kinetic[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_potential_n_e") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_potential_n_e));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_potential_n_e != 0) size_ao_1e_int_potential_n_e = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_potential_n_e; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_potential_n_e") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_potential_n_e[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_potential_n_e *= ao_1e_int->dims_ao_1e_int_potential_n_e[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_ecp") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_ecp));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_ecp != 0) size_ao_1e_int_ecp = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_ecp; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_ecp") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_ecp[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_ecp *= ao_1e_int->dims_ao_1e_int_ecp[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_core_hamiltonian") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_core_hamiltonian));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_core_hamiltonian != 0) size_ao_1e_int_core_hamiltonian = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_core_hamiltonian; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_core_hamiltonian") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_core_hamiltonian[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_core_hamiltonian *= ao_1e_int->dims_ao_1e_int_core_hamiltonian[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_overlap_im") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_overlap_im));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_overlap_im != 0) size_ao_1e_int_overlap_im = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_overlap_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_overlap_im") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_overlap_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_overlap_im *= ao_1e_int->dims_ao_1e_int_overlap_im[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_kinetic_im") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_kinetic_im));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_kinetic_im != 0) size_ao_1e_int_kinetic_im = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_kinetic_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_kinetic_im") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_kinetic_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_kinetic_im *= ao_1e_int->dims_ao_1e_int_kinetic_im[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_potential_n_e_im") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_potential_n_e_im));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_potential_n_e_im != 0) size_ao_1e_int_potential_n_e_im = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_potential_n_e_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_potential_n_e_im") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_potential_n_e_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_potential_n_e_im *= ao_1e_int->dims_ao_1e_int_potential_n_e_im[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_ecp_im") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_ecp_im));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_ecp_im != 0) size_ao_1e_int_ecp_im = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_ecp_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_ecp_im") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_ecp_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_ecp_im *= ao_1e_int->dims_ao_1e_int_ecp_im[i];
        }
      } else if (strcmp(buffer, "rank_ao_1e_int_core_hamiltonian_im") == 0) {

        rc = fscanf(f, "%u", &(ao_1e_int->rank_ao_1e_int_core_hamiltonian_im));
        if (rc != 1) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        if (ao_1e_int->rank_ao_1e_int_core_hamiltonian_im != 0) size_ao_1e_int_core_hamiltonian_im = 1UL;

        for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_core_hamiltonian_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_ao_1e_int_core_hamiltonian_im") != 0) || (j!=i)) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(ao_1e_int->dims_ao_1e_int_core_hamiltonian_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }

          size_ao_1e_int_core_hamiltonian_im *= ao_1e_int->dims_ao_1e_int_core_hamiltonian_im[i];
        }
      } else if (strcmp(buffer, "ao_1e_int_overlap") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_overlap = CALLOC(size_ao_1e_int_overlap, double);
        if (ao_1e_int->ao_1e_int_overlap == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_overlap ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_overlap[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_kinetic") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_kinetic = CALLOC(size_ao_1e_int_kinetic, double);
        if (ao_1e_int->ao_1e_int_kinetic == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_kinetic ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_kinetic[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_potential_n_e") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_potential_n_e = CALLOC(size_ao_1e_int_potential_n_e, double);
        if (ao_1e_int->ao_1e_int_potential_n_e == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_potential_n_e ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_potential_n_e[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_ecp") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_ecp = CALLOC(size_ao_1e_int_ecp, double);
        if (ao_1e_int->ao_1e_int_ecp == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_ecp ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_ecp[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_core_hamiltonian") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_core_hamiltonian = CALLOC(size_ao_1e_int_core_hamiltonian, double);
        if (ao_1e_int->ao_1e_int_core_hamiltonian == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_core_hamiltonian ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_core_hamiltonian[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_overlap_im") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_overlap_im = CALLOC(size_ao_1e_int_overlap_im, double);
        if (ao_1e_int->ao_1e_int_overlap_im == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_overlap_im ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_overlap_im[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_kinetic_im") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_kinetic_im = CALLOC(size_ao_1e_int_kinetic_im, double);
        if (ao_1e_int->ao_1e_int_kinetic_im == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_kinetic_im ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_kinetic_im[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_potential_n_e_im") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_potential_n_e_im = CALLOC(size_ao_1e_int_potential_n_e_im, double);
        if (ao_1e_int->ao_1e_int_potential_n_e_im == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_potential_n_e_im ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_potential_n_e_im[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_ecp_im") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_ecp_im = CALLOC(size_ao_1e_int_ecp_im, double);
        if (ao_1e_int->ao_1e_int_ecp_im == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_ecp_im ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_ecp_im[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "ao_1e_int_core_hamiltonian_im") == 0) {

        /* Allocate arrays */
        ao_1e_int->ao_1e_int_core_hamiltonian_im = CALLOC(size_ao_1e_int_core_hamiltonian_im, double);
        if (ao_1e_int->ao_1e_int_core_hamiltonian_im == NULL) {
          trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_ao_1e_int_core_hamiltonian_im ; ++i) {
          rc = fscanf(f, "%lf", &(ao_1e_int->ao_1e_int_core_hamiltonian_im[i]));
          if (rc != 1) {
            trexio_text_free_read_ao_1e_int(buffer, f, file, ao_1e_int);
            return NULL;
          }
        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->ao_1e_int = ao_1e_int;
  return ao_1e_int;
}

ao_2e_int_t*
trexio_text_read_ao_2e_int (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->ao_2e_int != NULL) {
    return file->ao_2e_int;
  }

  /* Allocate the data structure */
  ao_2e_int_t* ao_2e_int = MALLOC(ao_2e_int_t);
  if (ao_2e_int == NULL) return NULL;

  memset(ao_2e_int,0,sizeof(ao_2e_int_t));

  /* Build the file name */
  const char ao_2e_int_file_name[] = "/ao_2e_int.txt";

  strncpy (ao_2e_int->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  ao_2e_int->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (ao_2e_int->file_name, ao_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_file_name));

  if (ao_2e_int->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(ao_2e_int);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(ao_2e_int->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(ao_2e_int);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "ao_2e_int_eri_cholesky_num_isSet") == 0) {

        unsigned int ao_2e_int_eri_cholesky_num_isSet;
        /* additional parameter ao_2e_int_eri_cholesky_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(ao_2e_int_eri_cholesky_num_isSet));
        ao_2e_int->ao_2e_int_eri_cholesky_num_isSet = (bool) ao_2e_int_eri_cholesky_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_ao_2e_int(buffer, f, file, ao_2e_int);
          return NULL;
        }

        if (ao_2e_int->ao_2e_int_eri_cholesky_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "ao_2e_int_eri_cholesky_num") != 0)) {
            trexio_text_free_read_ao_2e_int(buffer, f, file, ao_2e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(ao_2e_int->ao_2e_int_eri_cholesky_num));
          if (rc != 1) {
            trexio_text_free_read_ao_2e_int(buffer, f, file, ao_2e_int);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "ao_2e_int_eri_lr_cholesky_num_isSet") == 0) {

        unsigned int ao_2e_int_eri_lr_cholesky_num_isSet;
        /* additional parameter ao_2e_int_eri_lr_cholesky_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(ao_2e_int_eri_lr_cholesky_num_isSet));
        ao_2e_int->ao_2e_int_eri_lr_cholesky_num_isSet = (bool) ao_2e_int_eri_lr_cholesky_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_ao_2e_int(buffer, f, file, ao_2e_int);
          return NULL;
        }

        if (ao_2e_int->ao_2e_int_eri_lr_cholesky_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "ao_2e_int_eri_lr_cholesky_num") != 0)) {
            trexio_text_free_read_ao_2e_int(buffer, f, file, ao_2e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(ao_2e_int->ao_2e_int_eri_lr_cholesky_num));
          if (rc != 1) {
            trexio_text_free_read_ao_2e_int(buffer, f, file, ao_2e_int);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->ao_2e_int = ao_2e_int;
  return ao_2e_int;
}

mo_t*
trexio_text_read_mo (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->mo != NULL) {
    return file->mo;
  }

  /* Allocate the data structure */
  mo_t* mo = MALLOC(mo_t);
  if (mo == NULL) return NULL;

  memset(mo,0,sizeof(mo_t));

  /* Build the file name */
  const char mo_file_name[] = "/mo.txt";

  strncpy (mo->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  mo->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (mo->file_name, mo_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_file_name));

  if (mo->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(mo);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(mo->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(mo);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_mo_coefficient = 0;
    uint64_t size_mo_coefficient_im = 0;
    uint64_t size_mo_occupation = 0;
    uint64_t size_mo_energy = 0;
    uint64_t size_mo_spin = 0;
    uint64_t size_mo_k_point = 0;
    uint64_t size_mo_class = 0;
    uint64_t size_mo_symmetry = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_mo_coefficient") == 0) {

        rc = fscanf(f, "%u", &(mo->rank_mo_coefficient));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->rank_mo_coefficient != 0) size_mo_coefficient = 1UL;

        for (uint32_t i=0; i<mo->rank_mo_coefficient; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_coefficient") != 0) || (j!=i)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo->dims_mo_coefficient[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          size_mo_coefficient *= mo->dims_mo_coefficient[i];
        }
      } else if (strcmp(buffer, "rank_mo_coefficient_im") == 0) {

        rc = fscanf(f, "%u", &(mo->rank_mo_coefficient_im));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->rank_mo_coefficient_im != 0) size_mo_coefficient_im = 1UL;

        for (uint32_t i=0; i<mo->rank_mo_coefficient_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_coefficient_im") != 0) || (j!=i)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo->dims_mo_coefficient_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          size_mo_coefficient_im *= mo->dims_mo_coefficient_im[i];
        }
      } else if (strcmp(buffer, "rank_mo_occupation") == 0) {

        rc = fscanf(f, "%u", &(mo->rank_mo_occupation));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->rank_mo_occupation != 0) size_mo_occupation = 1UL;

        for (uint32_t i=0; i<mo->rank_mo_occupation; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_occupation") != 0) || (j!=i)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo->dims_mo_occupation[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          size_mo_occupation *= mo->dims_mo_occupation[i];
        }
      } else if (strcmp(buffer, "rank_mo_energy") == 0) {

        rc = fscanf(f, "%u", &(mo->rank_mo_energy));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->rank_mo_energy != 0) size_mo_energy = 1UL;

        for (uint32_t i=0; i<mo->rank_mo_energy; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_energy") != 0) || (j!=i)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo->dims_mo_energy[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          size_mo_energy *= mo->dims_mo_energy[i];
        }
      } else if (strcmp(buffer, "rank_mo_spin") == 0) {

        rc = fscanf(f, "%u", &(mo->rank_mo_spin));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->rank_mo_spin != 0) size_mo_spin = 1UL;

        for (uint32_t i=0; i<mo->rank_mo_spin; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_spin") != 0) || (j!=i)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo->dims_mo_spin[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          size_mo_spin *= mo->dims_mo_spin[i];
        }
      } else if (strcmp(buffer, "rank_mo_k_point") == 0) {

        rc = fscanf(f, "%u", &(mo->rank_mo_k_point));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->rank_mo_k_point != 0) size_mo_k_point = 1UL;

        for (uint32_t i=0; i<mo->rank_mo_k_point; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_k_point") != 0) || (j!=i)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo->dims_mo_k_point[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          size_mo_k_point *= mo->dims_mo_k_point[i];
        }
      } else if (strcmp(buffer, "rank_mo_class") == 0) {

        rc = fscanf(f, "%u", &(mo->rank_mo_class));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->rank_mo_class != 0) size_mo_class = 1UL;

        for (uint32_t i=0; i<mo->rank_mo_class; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_class") != 0) || (j!=i)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo->dims_mo_class[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          size_mo_class *= mo->dims_mo_class[i];
        }
      } else if (strcmp(buffer, "rank_mo_symmetry") == 0) {

        rc = fscanf(f, "%u", &(mo->rank_mo_symmetry));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->rank_mo_symmetry != 0) size_mo_symmetry = 1UL;

        for (uint32_t i=0; i<mo->rank_mo_symmetry; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_symmetry") != 0) || (j!=i)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo->dims_mo_symmetry[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          size_mo_symmetry *= mo->dims_mo_symmetry[i];
        }
      } else if (strcmp(buffer, "mo_coefficient") == 0) {

        /* Allocate arrays */
        mo->mo_coefficient = CALLOC(size_mo_coefficient, double);
        if (mo->mo_coefficient == NULL) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_coefficient ; ++i) {
          rc = fscanf(f, "%lf", &(mo->mo_coefficient[i]));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_coefficient_im") == 0) {

        /* Allocate arrays */
        mo->mo_coefficient_im = CALLOC(size_mo_coefficient_im, double);
        if (mo->mo_coefficient_im == NULL) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_coefficient_im ; ++i) {
          rc = fscanf(f, "%lf", &(mo->mo_coefficient_im[i]));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_occupation") == 0) {

        /* Allocate arrays */
        mo->mo_occupation = CALLOC(size_mo_occupation, double);
        if (mo->mo_occupation == NULL) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_occupation ; ++i) {
          rc = fscanf(f, "%lf", &(mo->mo_occupation[i]));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_energy") == 0) {

        /* Allocate arrays */
        mo->mo_energy = CALLOC(size_mo_energy, double);
        if (mo->mo_energy == NULL) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_energy ; ++i) {
          rc = fscanf(f, "%lf", &(mo->mo_energy[i]));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_spin") == 0) {

        /* Allocate arrays */
        mo->mo_spin = CALLOC(size_mo_spin, int64_t);
        if (mo->mo_spin == NULL) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_spin ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(mo->mo_spin[i]));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_k_point") == 0) {

        /* Allocate arrays */
        mo->mo_k_point = CALLOC(size_mo_k_point, int64_t);
        if (mo->mo_k_point == NULL) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_k_point ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(mo->mo_k_point[i]));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_class") == 0) {

        if (size_mo_class != 0) {
          /* Allocate arrays */
          mo->mo_class = CALLOC(size_mo_class, char*);
          if (mo->mo_class == NULL) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          /* WARNING: this tmp array allows to avoid allocation of space for each element of array of string
           * BUT it's size has to be number_of_str*max_len_str where max_len_str is somewhat arbitrary, e.g. 32.
           */
          char* tmp_mo_class;
          tmp_mo_class = CALLOC(size_mo_class*32, char);

          for (uint64_t i=0 ; i<size_mo_class ; ++i) {
            mo->mo_class[i] = tmp_mo_class;
            /* conventional fcanf with "%s" only return the string before the first space character
             * to read string with spaces use "%[^\n]" possible with space before or after, i.e. " %[^\n]"
             */
            rc = fscanf(f, " %1023[^\n]", buffer);
            if (rc != 1) {
              trexio_text_free_read_mo(buffer, f, file, mo);
              return NULL;
            }

            size_t tmp_mo_class_len = strlen(buffer);
            strncpy(tmp_mo_class, buffer, 32);
            tmp_mo_class[31] = '\0';
            tmp_mo_class += tmp_mo_class_len + 1;
          }
        }

      } else if (strcmp(buffer, "mo_symmetry") == 0) {

        if (size_mo_symmetry != 0) {
          /* Allocate arrays */
          mo->mo_symmetry = CALLOC(size_mo_symmetry, char*);
          if (mo->mo_symmetry == NULL) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          /* WARNING: this tmp array allows to avoid allocation of space for each element of array of string
           * BUT it's size has to be number_of_str*max_len_str where max_len_str is somewhat arbitrary, e.g. 32.
           */
          char* tmp_mo_symmetry;
          tmp_mo_symmetry = CALLOC(size_mo_symmetry*32, char);

          for (uint64_t i=0 ; i<size_mo_symmetry ; ++i) {
            mo->mo_symmetry[i] = tmp_mo_symmetry;
            /* conventional fcanf with "%s" only return the string before the first space character
             * to read string with spaces use "%[^\n]" possible with space before or after, i.e. " %[^\n]"
             */
            rc = fscanf(f, " %1023[^\n]", buffer);
            if (rc != 1) {
              trexio_text_free_read_mo(buffer, f, file, mo);
              return NULL;
            }

            size_t tmp_mo_symmetry_len = strlen(buffer);
            strncpy(tmp_mo_symmetry, buffer, 32);
            tmp_mo_symmetry[31] = '\0';
            tmp_mo_symmetry += tmp_mo_symmetry_len + 1;
          }
        }

      } else if (strcmp(buffer, "mo_num_isSet") == 0) {

        unsigned int mo_num_isSet;
        /* additional parameter mo_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(mo_num_isSet));
        mo->mo_num_isSet = (bool) mo_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->mo_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "mo_num") != 0)) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(mo->mo_num));
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "len_mo_type") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(mo->len_mo_type));
        if (rc != 1) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "mo_type") != 0)) {
          trexio_text_free_read_mo(buffer, f, file, mo);
          return NULL;
        }

        if (mo->len_mo_type != 0) {

          mo->mo_type = CALLOC(mo->len_mo_type, char);
          if (mo->mo_type == NULL) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_mo(buffer, f, file, mo);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(mo->mo_type, buffer, mo->len_mo_type);
          mo->mo_type[mo->len_mo_type-1] = '\0';

        }
      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->mo = mo;
  return mo;
}

mo_1e_int_t*
trexio_text_read_mo_1e_int (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->mo_1e_int != NULL) {
    return file->mo_1e_int;
  }

  /* Allocate the data structure */
  mo_1e_int_t* mo_1e_int = MALLOC(mo_1e_int_t);
  if (mo_1e_int == NULL) return NULL;

  memset(mo_1e_int,0,sizeof(mo_1e_int_t));

  /* Build the file name */
  const char mo_1e_int_file_name[] = "/mo_1e_int.txt";

  strncpy (mo_1e_int->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  mo_1e_int->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (mo_1e_int->file_name, mo_1e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_1e_int_file_name));

  if (mo_1e_int->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(mo_1e_int);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(mo_1e_int->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(mo_1e_int);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_mo_1e_int_overlap = 0;
    uint64_t size_mo_1e_int_kinetic = 0;
    uint64_t size_mo_1e_int_potential_n_e = 0;
    uint64_t size_mo_1e_int_ecp = 0;
    uint64_t size_mo_1e_int_core_hamiltonian = 0;
    uint64_t size_mo_1e_int_overlap_im = 0;
    uint64_t size_mo_1e_int_kinetic_im = 0;
    uint64_t size_mo_1e_int_potential_n_e_im = 0;
    uint64_t size_mo_1e_int_ecp_im = 0;
    uint64_t size_mo_1e_int_core_hamiltonian_im = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_mo_1e_int_overlap") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_overlap));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_overlap != 0) size_mo_1e_int_overlap = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_overlap; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_overlap") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_overlap[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_overlap *= mo_1e_int->dims_mo_1e_int_overlap[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_kinetic") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_kinetic));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_kinetic != 0) size_mo_1e_int_kinetic = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_kinetic; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_kinetic") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_kinetic[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_kinetic *= mo_1e_int->dims_mo_1e_int_kinetic[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_potential_n_e") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_potential_n_e));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_potential_n_e != 0) size_mo_1e_int_potential_n_e = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_potential_n_e; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_potential_n_e") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_potential_n_e[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_potential_n_e *= mo_1e_int->dims_mo_1e_int_potential_n_e[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_ecp") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_ecp));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_ecp != 0) size_mo_1e_int_ecp = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_ecp; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_ecp") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_ecp[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_ecp *= mo_1e_int->dims_mo_1e_int_ecp[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_core_hamiltonian") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_core_hamiltonian));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_core_hamiltonian != 0) size_mo_1e_int_core_hamiltonian = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_core_hamiltonian; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_core_hamiltonian") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_core_hamiltonian[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_core_hamiltonian *= mo_1e_int->dims_mo_1e_int_core_hamiltonian[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_overlap_im") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_overlap_im));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_overlap_im != 0) size_mo_1e_int_overlap_im = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_overlap_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_overlap_im") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_overlap_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_overlap_im *= mo_1e_int->dims_mo_1e_int_overlap_im[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_kinetic_im") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_kinetic_im));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_kinetic_im != 0) size_mo_1e_int_kinetic_im = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_kinetic_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_kinetic_im") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_kinetic_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_kinetic_im *= mo_1e_int->dims_mo_1e_int_kinetic_im[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_potential_n_e_im") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_potential_n_e_im));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_potential_n_e_im != 0) size_mo_1e_int_potential_n_e_im = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_potential_n_e_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_potential_n_e_im") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_potential_n_e_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_potential_n_e_im *= mo_1e_int->dims_mo_1e_int_potential_n_e_im[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_ecp_im") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_ecp_im));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_ecp_im != 0) size_mo_1e_int_ecp_im = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_ecp_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_ecp_im") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_ecp_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_ecp_im *= mo_1e_int->dims_mo_1e_int_ecp_im[i];
        }
      } else if (strcmp(buffer, "rank_mo_1e_int_core_hamiltonian_im") == 0) {

        rc = fscanf(f, "%u", &(mo_1e_int->rank_mo_1e_int_core_hamiltonian_im));
        if (rc != 1) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        if (mo_1e_int->rank_mo_1e_int_core_hamiltonian_im != 0) size_mo_1e_int_core_hamiltonian_im = 1UL;

        for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_core_hamiltonian_im; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_mo_1e_int_core_hamiltonian_im") != 0) || (j!=i)) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(mo_1e_int->dims_mo_1e_int_core_hamiltonian_im[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }

          size_mo_1e_int_core_hamiltonian_im *= mo_1e_int->dims_mo_1e_int_core_hamiltonian_im[i];
        }
      } else if (strcmp(buffer, "mo_1e_int_overlap") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_overlap = CALLOC(size_mo_1e_int_overlap, double);
        if (mo_1e_int->mo_1e_int_overlap == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_overlap ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_overlap[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_kinetic") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_kinetic = CALLOC(size_mo_1e_int_kinetic, double);
        if (mo_1e_int->mo_1e_int_kinetic == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_kinetic ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_kinetic[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_potential_n_e") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_potential_n_e = CALLOC(size_mo_1e_int_potential_n_e, double);
        if (mo_1e_int->mo_1e_int_potential_n_e == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_potential_n_e ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_potential_n_e[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_ecp") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_ecp = CALLOC(size_mo_1e_int_ecp, double);
        if (mo_1e_int->mo_1e_int_ecp == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_ecp ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_ecp[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_core_hamiltonian") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_core_hamiltonian = CALLOC(size_mo_1e_int_core_hamiltonian, double);
        if (mo_1e_int->mo_1e_int_core_hamiltonian == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_core_hamiltonian ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_core_hamiltonian[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_overlap_im") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_overlap_im = CALLOC(size_mo_1e_int_overlap_im, double);
        if (mo_1e_int->mo_1e_int_overlap_im == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_overlap_im ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_overlap_im[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_kinetic_im") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_kinetic_im = CALLOC(size_mo_1e_int_kinetic_im, double);
        if (mo_1e_int->mo_1e_int_kinetic_im == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_kinetic_im ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_kinetic_im[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_potential_n_e_im") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_potential_n_e_im = CALLOC(size_mo_1e_int_potential_n_e_im, double);
        if (mo_1e_int->mo_1e_int_potential_n_e_im == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_potential_n_e_im ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_potential_n_e_im[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_ecp_im") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_ecp_im = CALLOC(size_mo_1e_int_ecp_im, double);
        if (mo_1e_int->mo_1e_int_ecp_im == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_ecp_im ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_ecp_im[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "mo_1e_int_core_hamiltonian_im") == 0) {

        /* Allocate arrays */
        mo_1e_int->mo_1e_int_core_hamiltonian_im = CALLOC(size_mo_1e_int_core_hamiltonian_im, double);
        if (mo_1e_int->mo_1e_int_core_hamiltonian_im == NULL) {
          trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_mo_1e_int_core_hamiltonian_im ; ++i) {
          rc = fscanf(f, "%lf", &(mo_1e_int->mo_1e_int_core_hamiltonian_im[i]));
          if (rc != 1) {
            trexio_text_free_read_mo_1e_int(buffer, f, file, mo_1e_int);
            return NULL;
          }
        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->mo_1e_int = mo_1e_int;
  return mo_1e_int;
}

mo_2e_int_t*
trexio_text_read_mo_2e_int (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->mo_2e_int != NULL) {
    return file->mo_2e_int;
  }

  /* Allocate the data structure */
  mo_2e_int_t* mo_2e_int = MALLOC(mo_2e_int_t);
  if (mo_2e_int == NULL) return NULL;

  memset(mo_2e_int,0,sizeof(mo_2e_int_t));

  /* Build the file name */
  const char mo_2e_int_file_name[] = "/mo_2e_int.txt";

  strncpy (mo_2e_int->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  mo_2e_int->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (mo_2e_int->file_name, mo_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_file_name));

  if (mo_2e_int->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(mo_2e_int);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(mo_2e_int->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(mo_2e_int);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "mo_2e_int_eri_cholesky_num_isSet") == 0) {

        unsigned int mo_2e_int_eri_cholesky_num_isSet;
        /* additional parameter mo_2e_int_eri_cholesky_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(mo_2e_int_eri_cholesky_num_isSet));
        mo_2e_int->mo_2e_int_eri_cholesky_num_isSet = (bool) mo_2e_int_eri_cholesky_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_mo_2e_int(buffer, f, file, mo_2e_int);
          return NULL;
        }

        if (mo_2e_int->mo_2e_int_eri_cholesky_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "mo_2e_int_eri_cholesky_num") != 0)) {
            trexio_text_free_read_mo_2e_int(buffer, f, file, mo_2e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(mo_2e_int->mo_2e_int_eri_cholesky_num));
          if (rc != 1) {
            trexio_text_free_read_mo_2e_int(buffer, f, file, mo_2e_int);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "mo_2e_int_eri_lr_cholesky_num_isSet") == 0) {

        unsigned int mo_2e_int_eri_lr_cholesky_num_isSet;
        /* additional parameter mo_2e_int_eri_lr_cholesky_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(mo_2e_int_eri_lr_cholesky_num_isSet));
        mo_2e_int->mo_2e_int_eri_lr_cholesky_num_isSet = (bool) mo_2e_int_eri_lr_cholesky_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_mo_2e_int(buffer, f, file, mo_2e_int);
          return NULL;
        }

        if (mo_2e_int->mo_2e_int_eri_lr_cholesky_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "mo_2e_int_eri_lr_cholesky_num") != 0)) {
            trexio_text_free_read_mo_2e_int(buffer, f, file, mo_2e_int);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(mo_2e_int->mo_2e_int_eri_lr_cholesky_num));
          if (rc != 1) {
            trexio_text_free_read_mo_2e_int(buffer, f, file, mo_2e_int);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->mo_2e_int = mo_2e_int;
  return mo_2e_int;
}

determinant_t*
trexio_text_read_determinant (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->determinant != NULL) {
    return file->determinant;
  }

  /* Allocate the data structure */
  determinant_t* determinant = MALLOC(determinant_t);
  if (determinant == NULL) return NULL;

  memset(determinant,0,sizeof(determinant_t));

  /* Build the file name */
  const char determinant_file_name[] = "/determinant.txt";

  strncpy (determinant->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  determinant->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (determinant->file_name, determinant_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(determinant_file_name));

  if (determinant->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(determinant);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(determinant->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(determinant);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "determinant_num_isSet") == 0) {

        unsigned int determinant_num_isSet;
        /* additional parameter determinant_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(determinant_num_isSet));
        determinant->determinant_num_isSet = (bool) determinant_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_determinant(buffer, f, file, determinant);
          return NULL;
        }

        if (determinant->determinant_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "determinant_num") != 0)) {
            trexio_text_free_read_determinant(buffer, f, file, determinant);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(determinant->determinant_num));
          if (rc != 1) {
            trexio_text_free_read_determinant(buffer, f, file, determinant);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->determinant = determinant;
  return determinant;
}

csf_t*
trexio_text_read_csf (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->csf != NULL) {
    return file->csf;
  }

  /* Allocate the data structure */
  csf_t* csf = MALLOC(csf_t);
  if (csf == NULL) return NULL;

  memset(csf,0,sizeof(csf_t));

  /* Build the file name */
  const char csf_file_name[] = "/csf.txt";

  strncpy (csf->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  csf->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (csf->file_name, csf_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(csf_file_name));

  if (csf->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(csf);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(csf->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(csf);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "csf_num_isSet") == 0) {

        unsigned int csf_num_isSet;
        /* additional parameter csf_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(csf_num_isSet));
        csf->csf_num_isSet = (bool) csf_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_csf(buffer, f, file, csf);
          return NULL;
        }

        if (csf->csf_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "csf_num") != 0)) {
            trexio_text_free_read_csf(buffer, f, file, csf);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(csf->csf_num));
          if (rc != 1) {
            trexio_text_free_read_csf(buffer, f, file, csf);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->csf = csf;
  return csf;
}

amplitude_t*
trexio_text_read_amplitude (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->amplitude != NULL) {
    return file->amplitude;
  }

  /* Allocate the data structure */
  amplitude_t* amplitude = MALLOC(amplitude_t);
  if (amplitude == NULL) return NULL;

  memset(amplitude,0,sizeof(amplitude_t));

  /* Build the file name */
  const char amplitude_file_name[] = "/amplitude.txt";

  strncpy (amplitude->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  amplitude->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (amplitude->file_name, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  if (amplitude->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(amplitude);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(amplitude->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(amplitude);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->amplitude = amplitude;
  return amplitude;
}

rdm_t*
trexio_text_read_rdm (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->rdm != NULL) {
    return file->rdm;
  }

  /* Allocate the data structure */
  rdm_t* rdm = MALLOC(rdm_t);
  if (rdm == NULL) return NULL;

  memset(rdm,0,sizeof(rdm_t));

  /* Build the file name */
  const char rdm_file_name[] = "/rdm.txt";

  strncpy (rdm->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  rdm->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (rdm->file_name, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  if (rdm->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(rdm);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(rdm->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(rdm);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_rdm_1e = 0;
    uint64_t size_rdm_1e_up = 0;
    uint64_t size_rdm_1e_dn = 0;
    uint64_t size_rdm_1e_transition = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_rdm_1e") == 0) {

        rc = fscanf(f, "%u", &(rdm->rank_rdm_1e));
        if (rc != 1) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        if (rdm->rank_rdm_1e != 0) size_rdm_1e = 1UL;

        for (uint32_t i=0; i<rdm->rank_rdm_1e; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_rdm_1e") != 0) || (j!=i)) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(rdm->dims_rdm_1e[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          size_rdm_1e *= rdm->dims_rdm_1e[i];
        }
      } else if (strcmp(buffer, "rank_rdm_1e_up") == 0) {

        rc = fscanf(f, "%u", &(rdm->rank_rdm_1e_up));
        if (rc != 1) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        if (rdm->rank_rdm_1e_up != 0) size_rdm_1e_up = 1UL;

        for (uint32_t i=0; i<rdm->rank_rdm_1e_up; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_rdm_1e_up") != 0) || (j!=i)) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(rdm->dims_rdm_1e_up[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          size_rdm_1e_up *= rdm->dims_rdm_1e_up[i];
        }
      } else if (strcmp(buffer, "rank_rdm_1e_dn") == 0) {

        rc = fscanf(f, "%u", &(rdm->rank_rdm_1e_dn));
        if (rc != 1) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        if (rdm->rank_rdm_1e_dn != 0) size_rdm_1e_dn = 1UL;

        for (uint32_t i=0; i<rdm->rank_rdm_1e_dn; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_rdm_1e_dn") != 0) || (j!=i)) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(rdm->dims_rdm_1e_dn[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          size_rdm_1e_dn *= rdm->dims_rdm_1e_dn[i];
        }
      } else if (strcmp(buffer, "rank_rdm_1e_transition") == 0) {

        rc = fscanf(f, "%u", &(rdm->rank_rdm_1e_transition));
        if (rc != 1) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        if (rdm->rank_rdm_1e_transition != 0) size_rdm_1e_transition = 1UL;

        for (uint32_t i=0; i<rdm->rank_rdm_1e_transition; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_rdm_1e_transition") != 0) || (j!=i)) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(rdm->dims_rdm_1e_transition[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          size_rdm_1e_transition *= rdm->dims_rdm_1e_transition[i];
        }
      } else if (strcmp(buffer, "rdm_1e") == 0) {

        /* Allocate arrays */
        rdm->rdm_1e = CALLOC(size_rdm_1e, double);
        if (rdm->rdm_1e == NULL) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_rdm_1e ; ++i) {
          rc = fscanf(f, "%lf", &(rdm->rdm_1e[i]));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "rdm_1e_up") == 0) {

        /* Allocate arrays */
        rdm->rdm_1e_up = CALLOC(size_rdm_1e_up, double);
        if (rdm->rdm_1e_up == NULL) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_rdm_1e_up ; ++i) {
          rc = fscanf(f, "%lf", &(rdm->rdm_1e_up[i]));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "rdm_1e_dn") == 0) {

        /* Allocate arrays */
        rdm->rdm_1e_dn = CALLOC(size_rdm_1e_dn, double);
        if (rdm->rdm_1e_dn == NULL) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_rdm_1e_dn ; ++i) {
          rc = fscanf(f, "%lf", &(rdm->rdm_1e_dn[i]));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "rdm_1e_transition") == 0) {

        /* Allocate arrays */
        rdm->rdm_1e_transition = CALLOC(size_rdm_1e_transition, double);
        if (rdm->rdm_1e_transition == NULL) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_rdm_1e_transition ; ++i) {
          rc = fscanf(f, "%lf", &(rdm->rdm_1e_transition[i]));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "rdm_2e_cholesky_num_isSet") == 0) {

        unsigned int rdm_2e_cholesky_num_isSet;
        /* additional parameter rdm_2e_cholesky_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(rdm_2e_cholesky_num_isSet));
        rdm->rdm_2e_cholesky_num_isSet = (bool) rdm_2e_cholesky_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        if (rdm->rdm_2e_cholesky_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "rdm_2e_cholesky_num") != 0)) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(rdm->rdm_2e_cholesky_num));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "rdm_2e_upup_cholesky_num_isSet") == 0) {

        unsigned int rdm_2e_upup_cholesky_num_isSet;
        /* additional parameter rdm_2e_upup_cholesky_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(rdm_2e_upup_cholesky_num_isSet));
        rdm->rdm_2e_upup_cholesky_num_isSet = (bool) rdm_2e_upup_cholesky_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        if (rdm->rdm_2e_upup_cholesky_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "rdm_2e_upup_cholesky_num") != 0)) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(rdm->rdm_2e_upup_cholesky_num));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "rdm_2e_dndn_cholesky_num_isSet") == 0) {

        unsigned int rdm_2e_dndn_cholesky_num_isSet;
        /* additional parameter rdm_2e_dndn_cholesky_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(rdm_2e_dndn_cholesky_num_isSet));
        rdm->rdm_2e_dndn_cholesky_num_isSet = (bool) rdm_2e_dndn_cholesky_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        if (rdm->rdm_2e_dndn_cholesky_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "rdm_2e_dndn_cholesky_num") != 0)) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(rdm->rdm_2e_dndn_cholesky_num));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "rdm_2e_updn_cholesky_num_isSet") == 0) {

        unsigned int rdm_2e_updn_cholesky_num_isSet;
        /* additional parameter rdm_2e_updn_cholesky_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(rdm_2e_updn_cholesky_num_isSet));
        rdm->rdm_2e_updn_cholesky_num_isSet = (bool) rdm_2e_updn_cholesky_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_rdm(buffer, f, file, rdm);
          return NULL;
        }

        if (rdm->rdm_2e_updn_cholesky_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "rdm_2e_updn_cholesky_num") != 0)) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(rdm->rdm_2e_updn_cholesky_num));
          if (rc != 1) {
            trexio_text_free_read_rdm(buffer, f, file, rdm);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->rdm = rdm;
  return rdm;
}

jastrow_t*
trexio_text_read_jastrow (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->jastrow != NULL) {
    return file->jastrow;
  }

  /* Allocate the data structure */
  jastrow_t* jastrow = MALLOC(jastrow_t);
  if (jastrow == NULL) return NULL;

  memset(jastrow,0,sizeof(jastrow_t));

  /* Build the file name */
  const char jastrow_file_name[] = "/jastrow.txt";

  strncpy (jastrow->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  jastrow->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (jastrow->file_name, jastrow_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(jastrow_file_name));

  if (jastrow->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(jastrow);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(jastrow->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(jastrow);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_jastrow_en = 0;
    uint64_t size_jastrow_ee = 0;
    uint64_t size_jastrow_een = 0;
    uint64_t size_jastrow_en_nucleus = 0;
    uint64_t size_jastrow_een_nucleus = 0;
    uint64_t size_jastrow_en_scaling = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_jastrow_en") == 0) {

        rc = fscanf(f, "%u", &(jastrow->rank_jastrow_en));
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->rank_jastrow_en != 0) size_jastrow_en = 1UL;

        for (uint32_t i=0; i<jastrow->rank_jastrow_en; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_jastrow_en") != 0) || (j!=i)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(jastrow->dims_jastrow_en[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          size_jastrow_en *= jastrow->dims_jastrow_en[i];
        }
      } else if (strcmp(buffer, "rank_jastrow_ee") == 0) {

        rc = fscanf(f, "%u", &(jastrow->rank_jastrow_ee));
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->rank_jastrow_ee != 0) size_jastrow_ee = 1UL;

        for (uint32_t i=0; i<jastrow->rank_jastrow_ee; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_jastrow_ee") != 0) || (j!=i)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(jastrow->dims_jastrow_ee[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          size_jastrow_ee *= jastrow->dims_jastrow_ee[i];
        }
      } else if (strcmp(buffer, "rank_jastrow_een") == 0) {

        rc = fscanf(f, "%u", &(jastrow->rank_jastrow_een));
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->rank_jastrow_een != 0) size_jastrow_een = 1UL;

        for (uint32_t i=0; i<jastrow->rank_jastrow_een; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_jastrow_een") != 0) || (j!=i)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(jastrow->dims_jastrow_een[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          size_jastrow_een *= jastrow->dims_jastrow_een[i];
        }
      } else if (strcmp(buffer, "rank_jastrow_en_nucleus") == 0) {

        rc = fscanf(f, "%u", &(jastrow->rank_jastrow_en_nucleus));
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->rank_jastrow_en_nucleus != 0) size_jastrow_en_nucleus = 1UL;

        for (uint32_t i=0; i<jastrow->rank_jastrow_en_nucleus; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_jastrow_en_nucleus") != 0) || (j!=i)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(jastrow->dims_jastrow_en_nucleus[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          size_jastrow_en_nucleus *= jastrow->dims_jastrow_en_nucleus[i];
        }
      } else if (strcmp(buffer, "rank_jastrow_een_nucleus") == 0) {

        rc = fscanf(f, "%u", &(jastrow->rank_jastrow_een_nucleus));
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->rank_jastrow_een_nucleus != 0) size_jastrow_een_nucleus = 1UL;

        for (uint32_t i=0; i<jastrow->rank_jastrow_een_nucleus; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_jastrow_een_nucleus") != 0) || (j!=i)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(jastrow->dims_jastrow_een_nucleus[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          size_jastrow_een_nucleus *= jastrow->dims_jastrow_een_nucleus[i];
        }
      } else if (strcmp(buffer, "rank_jastrow_en_scaling") == 0) {

        rc = fscanf(f, "%u", &(jastrow->rank_jastrow_en_scaling));
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->rank_jastrow_en_scaling != 0) size_jastrow_en_scaling = 1UL;

        for (uint32_t i=0; i<jastrow->rank_jastrow_en_scaling; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_jastrow_en_scaling") != 0) || (j!=i)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(jastrow->dims_jastrow_en_scaling[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          size_jastrow_en_scaling *= jastrow->dims_jastrow_en_scaling[i];
        }
      } else if (strcmp(buffer, "jastrow_en") == 0) {

        /* Allocate arrays */
        jastrow->jastrow_en = CALLOC(size_jastrow_en, double);
        if (jastrow->jastrow_en == NULL) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_jastrow_en ; ++i) {
          rc = fscanf(f, "%lf", &(jastrow->jastrow_en[i]));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "jastrow_ee") == 0) {

        /* Allocate arrays */
        jastrow->jastrow_ee = CALLOC(size_jastrow_ee, double);
        if (jastrow->jastrow_ee == NULL) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_jastrow_ee ; ++i) {
          rc = fscanf(f, "%lf", &(jastrow->jastrow_ee[i]));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "jastrow_een") == 0) {

        /* Allocate arrays */
        jastrow->jastrow_een = CALLOC(size_jastrow_een, double);
        if (jastrow->jastrow_een == NULL) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_jastrow_een ; ++i) {
          rc = fscanf(f, "%lf", &(jastrow->jastrow_een[i]));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "jastrow_en_nucleus") == 0) {

        /* Allocate arrays */
        jastrow->jastrow_en_nucleus = CALLOC(size_jastrow_en_nucleus, int64_t);
        if (jastrow->jastrow_en_nucleus == NULL) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_jastrow_en_nucleus ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(jastrow->jastrow_en_nucleus[i]));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "jastrow_een_nucleus") == 0) {

        /* Allocate arrays */
        jastrow->jastrow_een_nucleus = CALLOC(size_jastrow_een_nucleus, int64_t);
        if (jastrow->jastrow_een_nucleus == NULL) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_jastrow_een_nucleus ; ++i) {
          rc = fscanf(f, "%" SCNd64 "", &(jastrow->jastrow_een_nucleus[i]));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "jastrow_en_scaling") == 0) {

        /* Allocate arrays */
        jastrow->jastrow_en_scaling = CALLOC(size_jastrow_en_scaling, double);
        if (jastrow->jastrow_en_scaling == NULL) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_jastrow_en_scaling ; ++i) {
          rc = fscanf(f, "%lf", &(jastrow->jastrow_en_scaling[i]));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "jastrow_en_num_isSet") == 0) {

        unsigned int jastrow_en_num_isSet;
        /* additional parameter jastrow_en_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(jastrow_en_num_isSet));
        jastrow->jastrow_en_num_isSet = (bool) jastrow_en_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->jastrow_en_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "jastrow_en_num") != 0)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(jastrow->jastrow_en_num));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "jastrow_ee_num_isSet") == 0) {

        unsigned int jastrow_ee_num_isSet;
        /* additional parameter jastrow_ee_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(jastrow_ee_num_isSet));
        jastrow->jastrow_ee_num_isSet = (bool) jastrow_ee_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->jastrow_ee_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "jastrow_ee_num") != 0)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(jastrow->jastrow_ee_num));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "jastrow_een_num_isSet") == 0) {

        unsigned int jastrow_een_num_isSet;
        /* additional parameter jastrow_een_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(jastrow_een_num_isSet));
        jastrow->jastrow_een_num_isSet = (bool) jastrow_een_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->jastrow_een_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "jastrow_een_num") != 0)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(jastrow->jastrow_een_num));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "jastrow_ee_scaling_isSet") == 0) {

        unsigned int jastrow_ee_scaling_isSet;
        /* additional parameter jastrow_ee_scaling_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(jastrow_ee_scaling_isSet));
        jastrow->jastrow_ee_scaling_isSet = (bool) jastrow_ee_scaling_isSet;
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->jastrow_ee_scaling_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "jastrow_ee_scaling") != 0)) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, "%lf", &(jastrow->jastrow_ee_scaling));
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

        }

      } else if (strcmp(buffer, "len_jastrow_type") == 0) {

        rc = fscanf(f, "%" SCNu64 "", &(jastrow->len_jastrow_type));
        if (rc != 1) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        rc = fscanf(f, "%1023s", buffer);
        if ((rc != 1) || (strcmp(buffer, "jastrow_type") != 0)) {
          trexio_text_free_read_jastrow(buffer, f, file, jastrow);
          return NULL;
        }

        if (jastrow->len_jastrow_type != 0) {

          jastrow->jastrow_type = CALLOC(jastrow->len_jastrow_type, char);
          if (jastrow->jastrow_type == NULL) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }

          rc = fscanf(f, " %1023[^\n]", buffer);
          if (rc != 1) {
            trexio_text_free_read_jastrow(buffer, f, file, jastrow);
            return NULL;
          }
          /* Safer string conversion to avoid buffer overflow in fscanf */
          strncpy(jastrow->jastrow_type, buffer, jastrow->len_jastrow_type);
          jastrow->jastrow_type[jastrow->len_jastrow_type-1] = '\0';

        }
      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->jastrow = jastrow;
  return jastrow;
}

qmc_t*
trexio_text_read_qmc (trexio_text_t* const file)
{

  if (file == NULL) return NULL;

  /* If the data structure exists, return it */
  if (file->qmc != NULL) {
    return file->qmc;
  }

  /* Allocate the data structure */
  qmc_t* qmc = MALLOC(qmc_t);
  if (qmc == NULL) return NULL;

  memset(qmc,0,sizeof(qmc_t));

  /* Build the file name */
  const char qmc_file_name[] = "/qmc.txt";

  strncpy (qmc->file_name, file->parent.file_name, TREXIO_MAX_FILENAME_LENGTH);
  qmc->file_name[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  strncat (qmc->file_name, qmc_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(qmc_file_name));

  if (qmc->file_name[TREXIO_MAX_FILENAME_LENGTH-1] != '\0') {
    FREE(qmc);
    return NULL;
  }

  /* If the file exists, read it */
  FILE* f = fopen(qmc->file_name,"r");
  if (f != NULL) {

    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    sz = (sz < 1024) ? (1024) : (sz);
    char* buffer = CALLOC(sz, char);
    if (buffer == NULL) {
      fclose(f);
      FREE(qmc);
      return NULL;
    }

    int rc = 0;
    (void) rc;  // Avoid unused variable;
    trexio_exit_code rc_free = TREXIO_FAILURE;
    (void) rc_free;  // Avoid unused variable;

    /* workaround for the case of missing blocks in the file */
    uint64_t size_qmc_point = 0;
    uint64_t size_qmc_psi = 0;
    uint64_t size_qmc_e_loc = 0;

    while(fscanf(f, "%1023s", buffer) != EOF) {

      if (strcmp(buffer, "EXIT") == 0) {
        break;
      } else if (strcmp(buffer, "rank_qmc_point") == 0) {

        rc = fscanf(f, "%u", &(qmc->rank_qmc_point));
        if (rc != 1) {
          trexio_text_free_read_qmc(buffer, f, file, qmc);
          return NULL;
        }

        if (qmc->rank_qmc_point != 0) size_qmc_point = 1UL;

        for (uint32_t i=0; i<qmc->rank_qmc_point; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_qmc_point") != 0) || (j!=i)) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(qmc->dims_qmc_point[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }

          size_qmc_point *= qmc->dims_qmc_point[i];
        }
      } else if (strcmp(buffer, "rank_qmc_psi") == 0) {

        rc = fscanf(f, "%u", &(qmc->rank_qmc_psi));
        if (rc != 1) {
          trexio_text_free_read_qmc(buffer, f, file, qmc);
          return NULL;
        }

        if (qmc->rank_qmc_psi != 0) size_qmc_psi = 1UL;

        for (uint32_t i=0; i<qmc->rank_qmc_psi; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_qmc_psi") != 0) || (j!=i)) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(qmc->dims_qmc_psi[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }

          size_qmc_psi *= qmc->dims_qmc_psi[i];
        }
      } else if (strcmp(buffer, "rank_qmc_e_loc") == 0) {

        rc = fscanf(f, "%u", &(qmc->rank_qmc_e_loc));
        if (rc != 1) {
          trexio_text_free_read_qmc(buffer, f, file, qmc);
          return NULL;
        }

        if (qmc->rank_qmc_e_loc != 0) size_qmc_e_loc = 1UL;

        for (uint32_t i=0; i<qmc->rank_qmc_e_loc; ++i){

          uint32_t j=0;
          rc = fscanf(f, "%1023s %u", buffer, &j);
          if ((rc != 2) || (strcmp(buffer, "dims_qmc_e_loc") != 0) || (j!=i)) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }

          rc = fscanf(f, "%" SCNu64 "\n", &(qmc->dims_qmc_e_loc[i]));
          assert(!(rc != 1));
          if (rc != 1) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }

          size_qmc_e_loc *= qmc->dims_qmc_e_loc[i];
        }
      } else if (strcmp(buffer, "qmc_point") == 0) {

        /* Allocate arrays */
        qmc->qmc_point = CALLOC(size_qmc_point, double);
        if (qmc->qmc_point == NULL) {
          trexio_text_free_read_qmc(buffer, f, file, qmc);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_qmc_point ; ++i) {
          rc = fscanf(f, "%lf", &(qmc->qmc_point[i]));
          if (rc != 1) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "qmc_psi") == 0) {

        /* Allocate arrays */
        qmc->qmc_psi = CALLOC(size_qmc_psi, double);
        if (qmc->qmc_psi == NULL) {
          trexio_text_free_read_qmc(buffer, f, file, qmc);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_qmc_psi ; ++i) {
          rc = fscanf(f, "%lf", &(qmc->qmc_psi[i]));
          if (rc != 1) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "qmc_e_loc") == 0) {

        /* Allocate arrays */
        qmc->qmc_e_loc = CALLOC(size_qmc_e_loc, double);
        if (qmc->qmc_e_loc == NULL) {
          trexio_text_free_read_qmc(buffer, f, file, qmc);
          return NULL;
        }

        for (uint64_t i=0 ; i<size_qmc_e_loc ; ++i) {
          rc = fscanf(f, "%lf", &(qmc->qmc_e_loc[i]));
          if (rc != 1) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }
        }

      } else if (strcmp(buffer, "qmc_num_isSet") == 0) {

        unsigned int qmc_num_isSet;
        /* additional parameter qmc_num_isSet is needed to suppress warning when fscanf into bool variable using %u or %d */
        rc = fscanf(f, "%u", &(qmc_num_isSet));
        qmc->qmc_num_isSet = (bool) qmc_num_isSet;
        if (rc != 1) {
          trexio_text_free_read_qmc(buffer, f, file, qmc);
          return NULL;
        }

        if (qmc->qmc_num_isSet == true) {

          rc = fscanf(f, "%1023s", buffer);
          if ((rc != 1) || (strcmp(buffer, "qmc_num") != 0)) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }

          rc = fscanf(f, "%" SCNd64 "", &(qmc->qmc_num));
          if (rc != 1) {
            trexio_text_free_read_qmc(buffer, f, file, qmc);
            return NULL;
          }

        }

      } else {
        continue;
      }

    }

    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  file->qmc = qmc;
  return qmc;
}

trexio_exit_code
trexio_text_flush_metadata (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  metadata_t* metadata = file->metadata;
  if (metadata == NULL) return TREXIO_SUCCESS;

  if (metadata->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(metadata->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_metadata_code %u\n", metadata->rank_metadata_code);
  // workaround for the case of missing blocks in the file
  uint64_t size_metadata_code = 0;
  if (metadata->rank_metadata_code != 0) size_metadata_code = 1;

  for (unsigned int i=0; i<metadata->rank_metadata_code; ++i){
    fprintf(f, "dims_metadata_code %u %" PRIu64 "\n", i, metadata->dims_metadata_code[i]);
    size_metadata_code *= metadata->dims_metadata_code[i];
  }
  fprintf(f, "rank_metadata_author %u\n", metadata->rank_metadata_author);
  // workaround for the case of missing blocks in the file
  uint64_t size_metadata_author = 0;
  if (metadata->rank_metadata_author != 0) size_metadata_author = 1;

  for (unsigned int i=0; i<metadata->rank_metadata_author; ++i){
    fprintf(f, "dims_metadata_author %u %" PRIu64 "\n", i, metadata->dims_metadata_author[i]);
    size_metadata_author *= metadata->dims_metadata_author[i];
  }

  fprintf(f, "metadata_code_num_isSet %u \n", metadata->metadata_code_num_isSet);
  if (metadata->metadata_code_num_isSet == true) fprintf(f, "metadata_code_num %" PRId64 " \n", metadata->metadata_code_num);
  fprintf(f, "metadata_author_num_isSet %u \n", metadata->metadata_author_num_isSet);
  if (metadata->metadata_author_num_isSet == true) fprintf(f, "metadata_author_num %" PRId64 " \n", metadata->metadata_author_num);
  fprintf(f, "metadata_unsafe_isSet %u \n", metadata->metadata_unsafe_isSet);
  if (metadata->metadata_unsafe_isSet == true) fprintf(f, "metadata_unsafe %" PRId64 " \n", metadata->metadata_unsafe);

  fprintf(f, "len_metadata_package_version %" PRIu64 "\n", metadata->len_metadata_package_version);
  fprintf(f, "metadata_package_version\n");
  if (metadata->len_metadata_package_version != 0) fprintf(f, "%s\n", metadata->metadata_package_version);
  fprintf(f, "len_metadata_description %" PRIu64 "\n", metadata->len_metadata_description);
  fprintf(f, "metadata_description\n");
  if (metadata->len_metadata_description != 0) fprintf(f, "%s\n", metadata->metadata_description);

  /* Write arrays */

  fprintf(f, "metadata_code\n");
  for (uint64_t i=0 ; i<size_metadata_code ; ++i) {
    fprintf(f, "%s\n", metadata->metadata_code[i]);
  }

  fprintf(f, "metadata_author\n");
  for (uint64_t i=0 ; i<size_metadata_author ; ++i) {
    fprintf(f, "%s\n", metadata->metadata_author[i]);
  }

  fclose(f);
  metadata->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_nucleus (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  nucleus_t* nucleus = file->nucleus;
  if (nucleus == NULL) return TREXIO_SUCCESS;

  if (nucleus->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(nucleus->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_nucleus_charge %u\n", nucleus->rank_nucleus_charge);
  // workaround for the case of missing blocks in the file
  uint64_t size_nucleus_charge = 0;
  if (nucleus->rank_nucleus_charge != 0) size_nucleus_charge = 1;

  for (unsigned int i=0; i<nucleus->rank_nucleus_charge; ++i){
    fprintf(f, "dims_nucleus_charge %u %" PRIu64 "\n", i, nucleus->dims_nucleus_charge[i]);
    size_nucleus_charge *= nucleus->dims_nucleus_charge[i];
  }
  fprintf(f, "rank_nucleus_coord %u\n", nucleus->rank_nucleus_coord);
  // workaround for the case of missing blocks in the file
  uint64_t size_nucleus_coord = 0;
  if (nucleus->rank_nucleus_coord != 0) size_nucleus_coord = 1;

  for (unsigned int i=0; i<nucleus->rank_nucleus_coord; ++i){
    fprintf(f, "dims_nucleus_coord %u %" PRIu64 "\n", i, nucleus->dims_nucleus_coord[i]);
    size_nucleus_coord *= nucleus->dims_nucleus_coord[i];
  }
  fprintf(f, "rank_nucleus_label %u\n", nucleus->rank_nucleus_label);
  // workaround for the case of missing blocks in the file
  uint64_t size_nucleus_label = 0;
  if (nucleus->rank_nucleus_label != 0) size_nucleus_label = 1;

  for (unsigned int i=0; i<nucleus->rank_nucleus_label; ++i){
    fprintf(f, "dims_nucleus_label %u %" PRIu64 "\n", i, nucleus->dims_nucleus_label[i]);
    size_nucleus_label *= nucleus->dims_nucleus_label[i];
  }

  fprintf(f, "nucleus_num_isSet %u \n", nucleus->nucleus_num_isSet);
  if (nucleus->nucleus_num_isSet == true) fprintf(f, "nucleus_num %" PRId64 " \n", nucleus->nucleus_num);
  fprintf(f, "nucleus_repulsion_isSet %u \n", nucleus->nucleus_repulsion_isSet);
  if (nucleus->nucleus_repulsion_isSet == true) fprintf(f, "nucleus_repulsion %24.16e \n", nucleus->nucleus_repulsion);

  fprintf(f, "len_nucleus_point_group %" PRIu64 "\n", nucleus->len_nucleus_point_group);
  fprintf(f, "nucleus_point_group\n");
  if (nucleus->len_nucleus_point_group != 0) fprintf(f, "%s\n", nucleus->nucleus_point_group);

  /* Write arrays */

  fprintf(f, "nucleus_charge\n");
  for (uint64_t i=0 ; i<size_nucleus_charge ; ++i) {
    fprintf(f, "%24.16e\n", nucleus->nucleus_charge[i]);
  }

  fprintf(f, "nucleus_coord\n");
  for (uint64_t i=0 ; i<size_nucleus_coord ; ++i) {
    fprintf(f, "%24.16e\n", nucleus->nucleus_coord[i]);
  }

  fprintf(f, "nucleus_label\n");
  for (uint64_t i=0 ; i<size_nucleus_label ; ++i) {
    fprintf(f, "%s\n", nucleus->nucleus_label[i]);
  }

  fclose(f);
  nucleus->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_cell (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  cell_t* cell = file->cell;
  if (cell == NULL) return TREXIO_SUCCESS;

  if (cell->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(cell->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_cell_a %u\n", cell->rank_cell_a);
  // workaround for the case of missing blocks in the file
  uint64_t size_cell_a = 0;
  if (cell->rank_cell_a != 0) size_cell_a = 1;

  for (unsigned int i=0; i<cell->rank_cell_a; ++i){
    fprintf(f, "dims_cell_a %u %" PRIu64 "\n", i, cell->dims_cell_a[i]);
    size_cell_a *= cell->dims_cell_a[i];
  }
  fprintf(f, "rank_cell_b %u\n", cell->rank_cell_b);
  // workaround for the case of missing blocks in the file
  uint64_t size_cell_b = 0;
  if (cell->rank_cell_b != 0) size_cell_b = 1;

  for (unsigned int i=0; i<cell->rank_cell_b; ++i){
    fprintf(f, "dims_cell_b %u %" PRIu64 "\n", i, cell->dims_cell_b[i]);
    size_cell_b *= cell->dims_cell_b[i];
  }
  fprintf(f, "rank_cell_c %u\n", cell->rank_cell_c);
  // workaround for the case of missing blocks in the file
  uint64_t size_cell_c = 0;
  if (cell->rank_cell_c != 0) size_cell_c = 1;

  for (unsigned int i=0; i<cell->rank_cell_c; ++i){
    fprintf(f, "dims_cell_c %u %" PRIu64 "\n", i, cell->dims_cell_c[i]);
    size_cell_c *= cell->dims_cell_c[i];
  }
  fprintf(f, "rank_cell_g_a %u\n", cell->rank_cell_g_a);
  // workaround for the case of missing blocks in the file
  uint64_t size_cell_g_a = 0;
  if (cell->rank_cell_g_a != 0) size_cell_g_a = 1;

  for (unsigned int i=0; i<cell->rank_cell_g_a; ++i){
    fprintf(f, "dims_cell_g_a %u %" PRIu64 "\n", i, cell->dims_cell_g_a[i]);
    size_cell_g_a *= cell->dims_cell_g_a[i];
  }
  fprintf(f, "rank_cell_g_b %u\n", cell->rank_cell_g_b);
  // workaround for the case of missing blocks in the file
  uint64_t size_cell_g_b = 0;
  if (cell->rank_cell_g_b != 0) size_cell_g_b = 1;

  for (unsigned int i=0; i<cell->rank_cell_g_b; ++i){
    fprintf(f, "dims_cell_g_b %u %" PRIu64 "\n", i, cell->dims_cell_g_b[i]);
    size_cell_g_b *= cell->dims_cell_g_b[i];
  }
  fprintf(f, "rank_cell_g_c %u\n", cell->rank_cell_g_c);
  // workaround for the case of missing blocks in the file
  uint64_t size_cell_g_c = 0;
  if (cell->rank_cell_g_c != 0) size_cell_g_c = 1;

  for (unsigned int i=0; i<cell->rank_cell_g_c; ++i){
    fprintf(f, "dims_cell_g_c %u %" PRIu64 "\n", i, cell->dims_cell_g_c[i]);
    size_cell_g_c *= cell->dims_cell_g_c[i];
  }

  fprintf(f, "cell_two_pi_isSet %u \n", cell->cell_two_pi_isSet);
  if (cell->cell_two_pi_isSet == true) fprintf(f, "cell_two_pi %" PRId64 " \n", cell->cell_two_pi);


  /* Write arrays */

  fprintf(f, "cell_a\n");
  for (uint64_t i=0 ; i<size_cell_a ; ++i) {
    fprintf(f, "%24.16e\n", cell->cell_a[i]);
  }

  fprintf(f, "cell_b\n");
  for (uint64_t i=0 ; i<size_cell_b ; ++i) {
    fprintf(f, "%24.16e\n", cell->cell_b[i]);
  }

  fprintf(f, "cell_c\n");
  for (uint64_t i=0 ; i<size_cell_c ; ++i) {
    fprintf(f, "%24.16e\n", cell->cell_c[i]);
  }

  fprintf(f, "cell_g_a\n");
  for (uint64_t i=0 ; i<size_cell_g_a ; ++i) {
    fprintf(f, "%24.16e\n", cell->cell_g_a[i]);
  }

  fprintf(f, "cell_g_b\n");
  for (uint64_t i=0 ; i<size_cell_g_b ; ++i) {
    fprintf(f, "%24.16e\n", cell->cell_g_b[i]);
  }

  fprintf(f, "cell_g_c\n");
  for (uint64_t i=0 ; i<size_cell_g_c ; ++i) {
    fprintf(f, "%24.16e\n", cell->cell_g_c[i]);
  }

  fclose(f);
  cell->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_pbc (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  pbc_t* pbc = file->pbc;
  if (pbc == NULL) return TREXIO_SUCCESS;

  if (pbc->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(pbc->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_pbc_k_point %u\n", pbc->rank_pbc_k_point);
  // workaround for the case of missing blocks in the file
  uint64_t size_pbc_k_point = 0;
  if (pbc->rank_pbc_k_point != 0) size_pbc_k_point = 1;

  for (unsigned int i=0; i<pbc->rank_pbc_k_point; ++i){
    fprintf(f, "dims_pbc_k_point %u %" PRIu64 "\n", i, pbc->dims_pbc_k_point[i]);
    size_pbc_k_point *= pbc->dims_pbc_k_point[i];
  }
  fprintf(f, "rank_pbc_k_point_weight %u\n", pbc->rank_pbc_k_point_weight);
  // workaround for the case of missing blocks in the file
  uint64_t size_pbc_k_point_weight = 0;
  if (pbc->rank_pbc_k_point_weight != 0) size_pbc_k_point_weight = 1;

  for (unsigned int i=0; i<pbc->rank_pbc_k_point_weight; ++i){
    fprintf(f, "dims_pbc_k_point_weight %u %" PRIu64 "\n", i, pbc->dims_pbc_k_point_weight[i]);
    size_pbc_k_point_weight *= pbc->dims_pbc_k_point_weight[i];
  }

  fprintf(f, "pbc_periodic_isSet %u \n", pbc->pbc_periodic_isSet);
  if (pbc->pbc_periodic_isSet == true) fprintf(f, "pbc_periodic %" PRId64 " \n", pbc->pbc_periodic);
  fprintf(f, "pbc_k_point_num_isSet %u \n", pbc->pbc_k_point_num_isSet);
  if (pbc->pbc_k_point_num_isSet == true) fprintf(f, "pbc_k_point_num %" PRId64 " \n", pbc->pbc_k_point_num);
  fprintf(f, "pbc_madelung_isSet %u \n", pbc->pbc_madelung_isSet);
  if (pbc->pbc_madelung_isSet == true) fprintf(f, "pbc_madelung %24.16e \n", pbc->pbc_madelung);


  /* Write arrays */

  fprintf(f, "pbc_k_point\n");
  for (uint64_t i=0 ; i<size_pbc_k_point ; ++i) {
    fprintf(f, "%24.16e\n", pbc->pbc_k_point[i]);
  }

  fprintf(f, "pbc_k_point_weight\n");
  for (uint64_t i=0 ; i<size_pbc_k_point_weight ; ++i) {
    fprintf(f, "%24.16e\n", pbc->pbc_k_point_weight[i]);
  }

  fclose(f);
  pbc->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_electron (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  electron_t* electron = file->electron;
  if (electron == NULL) return TREXIO_SUCCESS;

  if (electron->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(electron->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */

  fprintf(f, "electron_num_isSet %u \n", electron->electron_num_isSet);
  if (electron->electron_num_isSet == true) fprintf(f, "electron_num %" PRId64 " \n", electron->electron_num);
  fprintf(f, "electron_up_num_isSet %u \n", electron->electron_up_num_isSet);
  if (electron->electron_up_num_isSet == true) fprintf(f, "electron_up_num %" PRId64 " \n", electron->electron_up_num);
  fprintf(f, "electron_dn_num_isSet %u \n", electron->electron_dn_num_isSet);
  if (electron->electron_dn_num_isSet == true) fprintf(f, "electron_dn_num %" PRId64 " \n", electron->electron_dn_num);


  /* Write arrays */

  fclose(f);
  electron->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_state (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  state_t* state = file->state;
  if (state == NULL) return TREXIO_SUCCESS;

  if (state->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(state->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_state_label %u\n", state->rank_state_label);
  // workaround for the case of missing blocks in the file
  uint64_t size_state_label = 0;
  if (state->rank_state_label != 0) size_state_label = 1;

  for (unsigned int i=0; i<state->rank_state_label; ++i){
    fprintf(f, "dims_state_label %u %" PRIu64 "\n", i, state->dims_state_label[i]);
    size_state_label *= state->dims_state_label[i];
  }
  fprintf(f, "rank_state_file_name %u\n", state->rank_state_file_name);
  // workaround for the case of missing blocks in the file
  uint64_t size_state_file_name = 0;
  if (state->rank_state_file_name != 0) size_state_file_name = 1;

  for (unsigned int i=0; i<state->rank_state_file_name; ++i){
    fprintf(f, "dims_state_file_name %u %" PRIu64 "\n", i, state->dims_state_file_name[i]);
    size_state_file_name *= state->dims_state_file_name[i];
  }

  fprintf(f, "state_num_isSet %u \n", state->state_num_isSet);
  if (state->state_num_isSet == true) fprintf(f, "state_num %" PRId64 " \n", state->state_num);
  fprintf(f, "state_id_isSet %u \n", state->state_id_isSet);
  if (state->state_id_isSet == true) fprintf(f, "state_id %" PRId64 " \n", state->state_id);
  fprintf(f, "state_energy_isSet %u \n", state->state_energy_isSet);
  if (state->state_energy_isSet == true) fprintf(f, "state_energy %24.16e \n", state->state_energy);

  fprintf(f, "len_state_current_label %" PRIu64 "\n", state->len_state_current_label);
  fprintf(f, "state_current_label\n");
  if (state->len_state_current_label != 0) fprintf(f, "%s\n", state->state_current_label);

  /* Write arrays */

  fprintf(f, "state_label\n");
  for (uint64_t i=0 ; i<size_state_label ; ++i) {
    fprintf(f, "%s\n", state->state_label[i]);
  }

  fprintf(f, "state_file_name\n");
  for (uint64_t i=0 ; i<size_state_file_name ; ++i) {
    fprintf(f, "%s\n", state->state_file_name[i]);
  }

  fclose(f);
  state->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_basis (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  basis_t* basis = file->basis;
  if (basis == NULL) return TREXIO_SUCCESS;

  if (basis->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(basis->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_basis_nucleus_index %u\n", basis->rank_basis_nucleus_index);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_nucleus_index = 0;
  if (basis->rank_basis_nucleus_index != 0) size_basis_nucleus_index = 1;

  for (unsigned int i=0; i<basis->rank_basis_nucleus_index; ++i){
    fprintf(f, "dims_basis_nucleus_index %u %" PRIu64 "\n", i, basis->dims_basis_nucleus_index[i]);
    size_basis_nucleus_index *= basis->dims_basis_nucleus_index[i];
  }
  fprintf(f, "rank_basis_shell_ang_mom %u\n", basis->rank_basis_shell_ang_mom);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_shell_ang_mom = 0;
  if (basis->rank_basis_shell_ang_mom != 0) size_basis_shell_ang_mom = 1;

  for (unsigned int i=0; i<basis->rank_basis_shell_ang_mom; ++i){
    fprintf(f, "dims_basis_shell_ang_mom %u %" PRIu64 "\n", i, basis->dims_basis_shell_ang_mom[i]);
    size_basis_shell_ang_mom *= basis->dims_basis_shell_ang_mom[i];
  }
  fprintf(f, "rank_basis_shell_factor %u\n", basis->rank_basis_shell_factor);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_shell_factor = 0;
  if (basis->rank_basis_shell_factor != 0) size_basis_shell_factor = 1;

  for (unsigned int i=0; i<basis->rank_basis_shell_factor; ++i){
    fprintf(f, "dims_basis_shell_factor %u %" PRIu64 "\n", i, basis->dims_basis_shell_factor[i]);
    size_basis_shell_factor *= basis->dims_basis_shell_factor[i];
  }
  fprintf(f, "rank_basis_r_power %u\n", basis->rank_basis_r_power);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_r_power = 0;
  if (basis->rank_basis_r_power != 0) size_basis_r_power = 1;

  for (unsigned int i=0; i<basis->rank_basis_r_power; ++i){
    fprintf(f, "dims_basis_r_power %u %" PRIu64 "\n", i, basis->dims_basis_r_power[i]);
    size_basis_r_power *= basis->dims_basis_r_power[i];
  }
  fprintf(f, "rank_basis_nao_grid_start %u\n", basis->rank_basis_nao_grid_start);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_nao_grid_start = 0;
  if (basis->rank_basis_nao_grid_start != 0) size_basis_nao_grid_start = 1;

  for (unsigned int i=0; i<basis->rank_basis_nao_grid_start; ++i){
    fprintf(f, "dims_basis_nao_grid_start %u %" PRIu64 "\n", i, basis->dims_basis_nao_grid_start[i]);
    size_basis_nao_grid_start *= basis->dims_basis_nao_grid_start[i];
  }
  fprintf(f, "rank_basis_nao_grid_size %u\n", basis->rank_basis_nao_grid_size);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_nao_grid_size = 0;
  if (basis->rank_basis_nao_grid_size != 0) size_basis_nao_grid_size = 1;

  for (unsigned int i=0; i<basis->rank_basis_nao_grid_size; ++i){
    fprintf(f, "dims_basis_nao_grid_size %u %" PRIu64 "\n", i, basis->dims_basis_nao_grid_size[i]);
    size_basis_nao_grid_size *= basis->dims_basis_nao_grid_size[i];
  }
  fprintf(f, "rank_basis_shell_index %u\n", basis->rank_basis_shell_index);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_shell_index = 0;
  if (basis->rank_basis_shell_index != 0) size_basis_shell_index = 1;

  for (unsigned int i=0; i<basis->rank_basis_shell_index; ++i){
    fprintf(f, "dims_basis_shell_index %u %" PRIu64 "\n", i, basis->dims_basis_shell_index[i]);
    size_basis_shell_index *= basis->dims_basis_shell_index[i];
  }
  fprintf(f, "rank_basis_exponent %u\n", basis->rank_basis_exponent);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_exponent = 0;
  if (basis->rank_basis_exponent != 0) size_basis_exponent = 1;

  for (unsigned int i=0; i<basis->rank_basis_exponent; ++i){
    fprintf(f, "dims_basis_exponent %u %" PRIu64 "\n", i, basis->dims_basis_exponent[i]);
    size_basis_exponent *= basis->dims_basis_exponent[i];
  }
  fprintf(f, "rank_basis_exponent_im %u\n", basis->rank_basis_exponent_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_exponent_im = 0;
  if (basis->rank_basis_exponent_im != 0) size_basis_exponent_im = 1;

  for (unsigned int i=0; i<basis->rank_basis_exponent_im; ++i){
    fprintf(f, "dims_basis_exponent_im %u %" PRIu64 "\n", i, basis->dims_basis_exponent_im[i]);
    size_basis_exponent_im *= basis->dims_basis_exponent_im[i];
  }
  fprintf(f, "rank_basis_coefficient %u\n", basis->rank_basis_coefficient);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_coefficient = 0;
  if (basis->rank_basis_coefficient != 0) size_basis_coefficient = 1;

  for (unsigned int i=0; i<basis->rank_basis_coefficient; ++i){
    fprintf(f, "dims_basis_coefficient %u %" PRIu64 "\n", i, basis->dims_basis_coefficient[i]);
    size_basis_coefficient *= basis->dims_basis_coefficient[i];
  }
  fprintf(f, "rank_basis_coefficient_im %u\n", basis->rank_basis_coefficient_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_coefficient_im = 0;
  if (basis->rank_basis_coefficient_im != 0) size_basis_coefficient_im = 1;

  for (unsigned int i=0; i<basis->rank_basis_coefficient_im; ++i){
    fprintf(f, "dims_basis_coefficient_im %u %" PRIu64 "\n", i, basis->dims_basis_coefficient_im[i]);
    size_basis_coefficient_im *= basis->dims_basis_coefficient_im[i];
  }
  fprintf(f, "rank_basis_oscillation_arg %u\n", basis->rank_basis_oscillation_arg);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_oscillation_arg = 0;
  if (basis->rank_basis_oscillation_arg != 0) size_basis_oscillation_arg = 1;

  for (unsigned int i=0; i<basis->rank_basis_oscillation_arg; ++i){
    fprintf(f, "dims_basis_oscillation_arg %u %" PRIu64 "\n", i, basis->dims_basis_oscillation_arg[i]);
    size_basis_oscillation_arg *= basis->dims_basis_oscillation_arg[i];
  }
  fprintf(f, "rank_basis_prim_factor %u\n", basis->rank_basis_prim_factor);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_prim_factor = 0;
  if (basis->rank_basis_prim_factor != 0) size_basis_prim_factor = 1;

  for (unsigned int i=0; i<basis->rank_basis_prim_factor; ++i){
    fprintf(f, "dims_basis_prim_factor %u %" PRIu64 "\n", i, basis->dims_basis_prim_factor[i]);
    size_basis_prim_factor *= basis->dims_basis_prim_factor[i];
  }
  fprintf(f, "rank_basis_nao_grid_radius %u\n", basis->rank_basis_nao_grid_radius);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_nao_grid_radius = 0;
  if (basis->rank_basis_nao_grid_radius != 0) size_basis_nao_grid_radius = 1;

  for (unsigned int i=0; i<basis->rank_basis_nao_grid_radius; ++i){
    fprintf(f, "dims_basis_nao_grid_radius %u %" PRIu64 "\n", i, basis->dims_basis_nao_grid_radius[i]);
    size_basis_nao_grid_radius *= basis->dims_basis_nao_grid_radius[i];
  }
  fprintf(f, "rank_basis_nao_grid_phi %u\n", basis->rank_basis_nao_grid_phi);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_nao_grid_phi = 0;
  if (basis->rank_basis_nao_grid_phi != 0) size_basis_nao_grid_phi = 1;

  for (unsigned int i=0; i<basis->rank_basis_nao_grid_phi; ++i){
    fprintf(f, "dims_basis_nao_grid_phi %u %" PRIu64 "\n", i, basis->dims_basis_nao_grid_phi[i]);
    size_basis_nao_grid_phi *= basis->dims_basis_nao_grid_phi[i];
  }
  fprintf(f, "rank_basis_nao_grid_grad %u\n", basis->rank_basis_nao_grid_grad);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_nao_grid_grad = 0;
  if (basis->rank_basis_nao_grid_grad != 0) size_basis_nao_grid_grad = 1;

  for (unsigned int i=0; i<basis->rank_basis_nao_grid_grad; ++i){
    fprintf(f, "dims_basis_nao_grid_grad %u %" PRIu64 "\n", i, basis->dims_basis_nao_grid_grad[i]);
    size_basis_nao_grid_grad *= basis->dims_basis_nao_grid_grad[i];
  }
  fprintf(f, "rank_basis_nao_grid_lap %u\n", basis->rank_basis_nao_grid_lap);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_nao_grid_lap = 0;
  if (basis->rank_basis_nao_grid_lap != 0) size_basis_nao_grid_lap = 1;

  for (unsigned int i=0; i<basis->rank_basis_nao_grid_lap; ++i){
    fprintf(f, "dims_basis_nao_grid_lap %u %" PRIu64 "\n", i, basis->dims_basis_nao_grid_lap[i]);
    size_basis_nao_grid_lap *= basis->dims_basis_nao_grid_lap[i];
  }
  fprintf(f, "rank_basis_interpolator_phi %u\n", basis->rank_basis_interpolator_phi);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_interpolator_phi = 0;
  if (basis->rank_basis_interpolator_phi != 0) size_basis_interpolator_phi = 1;

  for (unsigned int i=0; i<basis->rank_basis_interpolator_phi; ++i){
    fprintf(f, "dims_basis_interpolator_phi %u %" PRIu64 "\n", i, basis->dims_basis_interpolator_phi[i]);
    size_basis_interpolator_phi *= basis->dims_basis_interpolator_phi[i];
  }
  fprintf(f, "rank_basis_interpolator_grad %u\n", basis->rank_basis_interpolator_grad);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_interpolator_grad = 0;
  if (basis->rank_basis_interpolator_grad != 0) size_basis_interpolator_grad = 1;

  for (unsigned int i=0; i<basis->rank_basis_interpolator_grad; ++i){
    fprintf(f, "dims_basis_interpolator_grad %u %" PRIu64 "\n", i, basis->dims_basis_interpolator_grad[i]);
    size_basis_interpolator_grad *= basis->dims_basis_interpolator_grad[i];
  }
  fprintf(f, "rank_basis_interpolator_lap %u\n", basis->rank_basis_interpolator_lap);
  // workaround for the case of missing blocks in the file
  uint64_t size_basis_interpolator_lap = 0;
  if (basis->rank_basis_interpolator_lap != 0) size_basis_interpolator_lap = 1;

  for (unsigned int i=0; i<basis->rank_basis_interpolator_lap; ++i){
    fprintf(f, "dims_basis_interpolator_lap %u %" PRIu64 "\n", i, basis->dims_basis_interpolator_lap[i]);
    size_basis_interpolator_lap *= basis->dims_basis_interpolator_lap[i];
  }

  fprintf(f, "basis_prim_num_isSet %u \n", basis->basis_prim_num_isSet);
  if (basis->basis_prim_num_isSet == true) fprintf(f, "basis_prim_num %" PRId64 " \n", basis->basis_prim_num);
  fprintf(f, "basis_shell_num_isSet %u \n", basis->basis_shell_num_isSet);
  if (basis->basis_shell_num_isSet == true) fprintf(f, "basis_shell_num %" PRId64 " \n", basis->basis_shell_num);
  fprintf(f, "basis_nao_grid_num_isSet %u \n", basis->basis_nao_grid_num_isSet);
  if (basis->basis_nao_grid_num_isSet == true) fprintf(f, "basis_nao_grid_num %" PRId64 " \n", basis->basis_nao_grid_num);
  fprintf(f, "basis_interp_coeff_cnt_isSet %u \n", basis->basis_interp_coeff_cnt_isSet);
  if (basis->basis_interp_coeff_cnt_isSet == true) fprintf(f, "basis_interp_coeff_cnt %" PRId64 " \n", basis->basis_interp_coeff_cnt);
  fprintf(f, "basis_e_cut_isSet %u \n", basis->basis_e_cut_isSet);
  if (basis->basis_e_cut_isSet == true) fprintf(f, "basis_e_cut %24.16e \n", basis->basis_e_cut);

  fprintf(f, "len_basis_type %" PRIu64 "\n", basis->len_basis_type);
  fprintf(f, "basis_type\n");
  if (basis->len_basis_type != 0) fprintf(f, "%s\n", basis->basis_type);
  fprintf(f, "len_basis_oscillation_kind %" PRIu64 "\n", basis->len_basis_oscillation_kind);
  fprintf(f, "basis_oscillation_kind\n");
  if (basis->len_basis_oscillation_kind != 0) fprintf(f, "%s\n", basis->basis_oscillation_kind);
  fprintf(f, "len_basis_interpolator_kind %" PRIu64 "\n", basis->len_basis_interpolator_kind);
  fprintf(f, "basis_interpolator_kind\n");
  if (basis->len_basis_interpolator_kind != 0) fprintf(f, "%s\n", basis->basis_interpolator_kind);

  /* Write arrays */

  fprintf(f, "basis_nucleus_index\n");
  for (uint64_t i=0 ; i<size_basis_nucleus_index ; ++i) {
    fprintf(f, "%" PRId64 "\n", basis->basis_nucleus_index[i]);
  }

  fprintf(f, "basis_shell_ang_mom\n");
  for (uint64_t i=0 ; i<size_basis_shell_ang_mom ; ++i) {
    fprintf(f, "%" PRId64 "\n", basis->basis_shell_ang_mom[i]);
  }

  fprintf(f, "basis_shell_factor\n");
  for (uint64_t i=0 ; i<size_basis_shell_factor ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_shell_factor[i]);
  }

  fprintf(f, "basis_r_power\n");
  for (uint64_t i=0 ; i<size_basis_r_power ; ++i) {
    fprintf(f, "%" PRId64 "\n", basis->basis_r_power[i]);
  }

  fprintf(f, "basis_nao_grid_start\n");
  for (uint64_t i=0 ; i<size_basis_nao_grid_start ; ++i) {
    fprintf(f, "%" PRId64 "\n", basis->basis_nao_grid_start[i]);
  }

  fprintf(f, "basis_nao_grid_size\n");
  for (uint64_t i=0 ; i<size_basis_nao_grid_size ; ++i) {
    fprintf(f, "%" PRId64 "\n", basis->basis_nao_grid_size[i]);
  }

  fprintf(f, "basis_shell_index\n");
  for (uint64_t i=0 ; i<size_basis_shell_index ; ++i) {
    fprintf(f, "%" PRId64 "\n", basis->basis_shell_index[i]);
  }

  fprintf(f, "basis_exponent\n");
  for (uint64_t i=0 ; i<size_basis_exponent ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_exponent[i]);
  }

  fprintf(f, "basis_exponent_im\n");
  for (uint64_t i=0 ; i<size_basis_exponent_im ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_exponent_im[i]);
  }

  fprintf(f, "basis_coefficient\n");
  for (uint64_t i=0 ; i<size_basis_coefficient ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_coefficient[i]);
  }

  fprintf(f, "basis_coefficient_im\n");
  for (uint64_t i=0 ; i<size_basis_coefficient_im ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_coefficient_im[i]);
  }

  fprintf(f, "basis_oscillation_arg\n");
  for (uint64_t i=0 ; i<size_basis_oscillation_arg ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_oscillation_arg[i]);
  }

  fprintf(f, "basis_prim_factor\n");
  for (uint64_t i=0 ; i<size_basis_prim_factor ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_prim_factor[i]);
  }

  fprintf(f, "basis_nao_grid_radius\n");
  for (uint64_t i=0 ; i<size_basis_nao_grid_radius ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_nao_grid_radius[i]);
  }

  fprintf(f, "basis_nao_grid_phi\n");
  for (uint64_t i=0 ; i<size_basis_nao_grid_phi ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_nao_grid_phi[i]);
  }

  fprintf(f, "basis_nao_grid_grad\n");
  for (uint64_t i=0 ; i<size_basis_nao_grid_grad ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_nao_grid_grad[i]);
  }

  fprintf(f, "basis_nao_grid_lap\n");
  for (uint64_t i=0 ; i<size_basis_nao_grid_lap ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_nao_grid_lap[i]);
  }

  fprintf(f, "basis_interpolator_phi\n");
  for (uint64_t i=0 ; i<size_basis_interpolator_phi ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_interpolator_phi[i]);
  }

  fprintf(f, "basis_interpolator_grad\n");
  for (uint64_t i=0 ; i<size_basis_interpolator_grad ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_interpolator_grad[i]);
  }

  fprintf(f, "basis_interpolator_lap\n");
  for (uint64_t i=0 ; i<size_basis_interpolator_lap ; ++i) {
    fprintf(f, "%24.16e\n", basis->basis_interpolator_lap[i]);
  }

  fclose(f);
  basis->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_ecp (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = file->ecp;
  if (ecp == NULL) return TREXIO_SUCCESS;

  if (ecp->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(ecp->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_ecp_max_ang_mom_plus_1 %u\n", ecp->rank_ecp_max_ang_mom_plus_1);
  // workaround for the case of missing blocks in the file
  uint64_t size_ecp_max_ang_mom_plus_1 = 0;
  if (ecp->rank_ecp_max_ang_mom_plus_1 != 0) size_ecp_max_ang_mom_plus_1 = 1;

  for (unsigned int i=0; i<ecp->rank_ecp_max_ang_mom_plus_1; ++i){
    fprintf(f, "dims_ecp_max_ang_mom_plus_1 %u %" PRIu64 "\n", i, ecp->dims_ecp_max_ang_mom_plus_1[i]);
    size_ecp_max_ang_mom_plus_1 *= ecp->dims_ecp_max_ang_mom_plus_1[i];
  }
  fprintf(f, "rank_ecp_z_core %u\n", ecp->rank_ecp_z_core);
  // workaround for the case of missing blocks in the file
  uint64_t size_ecp_z_core = 0;
  if (ecp->rank_ecp_z_core != 0) size_ecp_z_core = 1;

  for (unsigned int i=0; i<ecp->rank_ecp_z_core; ++i){
    fprintf(f, "dims_ecp_z_core %u %" PRIu64 "\n", i, ecp->dims_ecp_z_core[i]);
    size_ecp_z_core *= ecp->dims_ecp_z_core[i];
  }
  fprintf(f, "rank_ecp_ang_mom %u\n", ecp->rank_ecp_ang_mom);
  // workaround for the case of missing blocks in the file
  uint64_t size_ecp_ang_mom = 0;
  if (ecp->rank_ecp_ang_mom != 0) size_ecp_ang_mom = 1;

  for (unsigned int i=0; i<ecp->rank_ecp_ang_mom; ++i){
    fprintf(f, "dims_ecp_ang_mom %u %" PRIu64 "\n", i, ecp->dims_ecp_ang_mom[i]);
    size_ecp_ang_mom *= ecp->dims_ecp_ang_mom[i];
  }
  fprintf(f, "rank_ecp_nucleus_index %u\n", ecp->rank_ecp_nucleus_index);
  // workaround for the case of missing blocks in the file
  uint64_t size_ecp_nucleus_index = 0;
  if (ecp->rank_ecp_nucleus_index != 0) size_ecp_nucleus_index = 1;

  for (unsigned int i=0; i<ecp->rank_ecp_nucleus_index; ++i){
    fprintf(f, "dims_ecp_nucleus_index %u %" PRIu64 "\n", i, ecp->dims_ecp_nucleus_index[i]);
    size_ecp_nucleus_index *= ecp->dims_ecp_nucleus_index[i];
  }
  fprintf(f, "rank_ecp_exponent %u\n", ecp->rank_ecp_exponent);
  // workaround for the case of missing blocks in the file
  uint64_t size_ecp_exponent = 0;
  if (ecp->rank_ecp_exponent != 0) size_ecp_exponent = 1;

  for (unsigned int i=0; i<ecp->rank_ecp_exponent; ++i){
    fprintf(f, "dims_ecp_exponent %u %" PRIu64 "\n", i, ecp->dims_ecp_exponent[i]);
    size_ecp_exponent *= ecp->dims_ecp_exponent[i];
  }
  fprintf(f, "rank_ecp_coefficient %u\n", ecp->rank_ecp_coefficient);
  // workaround for the case of missing blocks in the file
  uint64_t size_ecp_coefficient = 0;
  if (ecp->rank_ecp_coefficient != 0) size_ecp_coefficient = 1;

  for (unsigned int i=0; i<ecp->rank_ecp_coefficient; ++i){
    fprintf(f, "dims_ecp_coefficient %u %" PRIu64 "\n", i, ecp->dims_ecp_coefficient[i]);
    size_ecp_coefficient *= ecp->dims_ecp_coefficient[i];
  }
  fprintf(f, "rank_ecp_power %u\n", ecp->rank_ecp_power);
  // workaround for the case of missing blocks in the file
  uint64_t size_ecp_power = 0;
  if (ecp->rank_ecp_power != 0) size_ecp_power = 1;

  for (unsigned int i=0; i<ecp->rank_ecp_power; ++i){
    fprintf(f, "dims_ecp_power %u %" PRIu64 "\n", i, ecp->dims_ecp_power[i]);
    size_ecp_power *= ecp->dims_ecp_power[i];
  }

  fprintf(f, "ecp_num_isSet %u \n", ecp->ecp_num_isSet);
  if (ecp->ecp_num_isSet == true) fprintf(f, "ecp_num %" PRId64 " \n", ecp->ecp_num);


  /* Write arrays */

  fprintf(f, "ecp_max_ang_mom_plus_1\n");
  for (uint64_t i=0 ; i<size_ecp_max_ang_mom_plus_1 ; ++i) {
    fprintf(f, "%" PRId64 "\n", ecp->ecp_max_ang_mom_plus_1[i]);
  }

  fprintf(f, "ecp_z_core\n");
  for (uint64_t i=0 ; i<size_ecp_z_core ; ++i) {
    fprintf(f, "%" PRId64 "\n", ecp->ecp_z_core[i]);
  }

  fprintf(f, "ecp_ang_mom\n");
  for (uint64_t i=0 ; i<size_ecp_ang_mom ; ++i) {
    fprintf(f, "%" PRId64 "\n", ecp->ecp_ang_mom[i]);
  }

  fprintf(f, "ecp_nucleus_index\n");
  for (uint64_t i=0 ; i<size_ecp_nucleus_index ; ++i) {
    fprintf(f, "%" PRId64 "\n", ecp->ecp_nucleus_index[i]);
  }

  fprintf(f, "ecp_exponent\n");
  for (uint64_t i=0 ; i<size_ecp_exponent ; ++i) {
    fprintf(f, "%24.16e\n", ecp->ecp_exponent[i]);
  }

  fprintf(f, "ecp_coefficient\n");
  for (uint64_t i=0 ; i<size_ecp_coefficient ; ++i) {
    fprintf(f, "%24.16e\n", ecp->ecp_coefficient[i]);
  }

  fprintf(f, "ecp_power\n");
  for (uint64_t i=0 ; i<size_ecp_power ; ++i) {
    fprintf(f, "%" PRId64 "\n", ecp->ecp_power[i]);
  }

  fclose(f);
  ecp->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_grid (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  grid_t* grid = file->grid;
  if (grid == NULL) return TREXIO_SUCCESS;

  if (grid->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(grid->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_grid_coord %u\n", grid->rank_grid_coord);
  // workaround for the case of missing blocks in the file
  uint64_t size_grid_coord = 0;
  if (grid->rank_grid_coord != 0) size_grid_coord = 1;

  for (unsigned int i=0; i<grid->rank_grid_coord; ++i){
    fprintf(f, "dims_grid_coord %u %" PRIu64 "\n", i, grid->dims_grid_coord[i]);
    size_grid_coord *= grid->dims_grid_coord[i];
  }
  fprintf(f, "rank_grid_weight %u\n", grid->rank_grid_weight);
  // workaround for the case of missing blocks in the file
  uint64_t size_grid_weight = 0;
  if (grid->rank_grid_weight != 0) size_grid_weight = 1;

  for (unsigned int i=0; i<grid->rank_grid_weight; ++i){
    fprintf(f, "dims_grid_weight %u %" PRIu64 "\n", i, grid->dims_grid_weight[i]);
    size_grid_weight *= grid->dims_grid_weight[i];
  }
  fprintf(f, "rank_grid_ang_coord %u\n", grid->rank_grid_ang_coord);
  // workaround for the case of missing blocks in the file
  uint64_t size_grid_ang_coord = 0;
  if (grid->rank_grid_ang_coord != 0) size_grid_ang_coord = 1;

  for (unsigned int i=0; i<grid->rank_grid_ang_coord; ++i){
    fprintf(f, "dims_grid_ang_coord %u %" PRIu64 "\n", i, grid->dims_grid_ang_coord[i]);
    size_grid_ang_coord *= grid->dims_grid_ang_coord[i];
  }
  fprintf(f, "rank_grid_ang_weight %u\n", grid->rank_grid_ang_weight);
  // workaround for the case of missing blocks in the file
  uint64_t size_grid_ang_weight = 0;
  if (grid->rank_grid_ang_weight != 0) size_grid_ang_weight = 1;

  for (unsigned int i=0; i<grid->rank_grid_ang_weight; ++i){
    fprintf(f, "dims_grid_ang_weight %u %" PRIu64 "\n", i, grid->dims_grid_ang_weight[i]);
    size_grid_ang_weight *= grid->dims_grid_ang_weight[i];
  }
  fprintf(f, "rank_grid_rad_coord %u\n", grid->rank_grid_rad_coord);
  // workaround for the case of missing blocks in the file
  uint64_t size_grid_rad_coord = 0;
  if (grid->rank_grid_rad_coord != 0) size_grid_rad_coord = 1;

  for (unsigned int i=0; i<grid->rank_grid_rad_coord; ++i){
    fprintf(f, "dims_grid_rad_coord %u %" PRIu64 "\n", i, grid->dims_grid_rad_coord[i]);
    size_grid_rad_coord *= grid->dims_grid_rad_coord[i];
  }
  fprintf(f, "rank_grid_rad_weight %u\n", grid->rank_grid_rad_weight);
  // workaround for the case of missing blocks in the file
  uint64_t size_grid_rad_weight = 0;
  if (grid->rank_grid_rad_weight != 0) size_grid_rad_weight = 1;

  for (unsigned int i=0; i<grid->rank_grid_rad_weight; ++i){
    fprintf(f, "dims_grid_rad_weight %u %" PRIu64 "\n", i, grid->dims_grid_rad_weight[i]);
    size_grid_rad_weight *= grid->dims_grid_rad_weight[i];
  }

  fprintf(f, "grid_rad_precision_isSet %u \n", grid->grid_rad_precision_isSet);
  if (grid->grid_rad_precision_isSet == true) fprintf(f, "grid_rad_precision %24.16e \n", grid->grid_rad_precision);
  fprintf(f, "grid_num_isSet %u \n", grid->grid_num_isSet);
  if (grid->grid_num_isSet == true) fprintf(f, "grid_num %" PRId64 " \n", grid->grid_num);
  fprintf(f, "grid_max_ang_num_isSet %u \n", grid->grid_max_ang_num_isSet);
  if (grid->grid_max_ang_num_isSet == true) fprintf(f, "grid_max_ang_num %" PRId64 " \n", grid->grid_max_ang_num);
  fprintf(f, "grid_min_ang_num_isSet %u \n", grid->grid_min_ang_num_isSet);
  if (grid->grid_min_ang_num_isSet == true) fprintf(f, "grid_min_ang_num %" PRId64 " \n", grid->grid_min_ang_num);
  fprintf(f, "grid_ang_num_isSet %u \n", grid->grid_ang_num_isSet);
  if (grid->grid_ang_num_isSet == true) fprintf(f, "grid_ang_num %" PRId64 " \n", grid->grid_ang_num);
  fprintf(f, "grid_rad_num_isSet %u \n", grid->grid_rad_num_isSet);
  if (grid->grid_rad_num_isSet == true) fprintf(f, "grid_rad_num %" PRId64 " \n", grid->grid_rad_num);

  fprintf(f, "len_grid_description %" PRIu64 "\n", grid->len_grid_description);
  fprintf(f, "grid_description\n");
  if (grid->len_grid_description != 0) fprintf(f, "%s\n", grid->grid_description);

  /* Write arrays */

  fprintf(f, "grid_coord\n");
  for (uint64_t i=0 ; i<size_grid_coord ; ++i) {
    fprintf(f, "%24.16e\n", grid->grid_coord[i]);
  }

  fprintf(f, "grid_weight\n");
  for (uint64_t i=0 ; i<size_grid_weight ; ++i) {
    fprintf(f, "%24.16e\n", grid->grid_weight[i]);
  }

  fprintf(f, "grid_ang_coord\n");
  for (uint64_t i=0 ; i<size_grid_ang_coord ; ++i) {
    fprintf(f, "%24.16e\n", grid->grid_ang_coord[i]);
  }

  fprintf(f, "grid_ang_weight\n");
  for (uint64_t i=0 ; i<size_grid_ang_weight ; ++i) {
    fprintf(f, "%24.16e\n", grid->grid_ang_weight[i]);
  }

  fprintf(f, "grid_rad_coord\n");
  for (uint64_t i=0 ; i<size_grid_rad_coord ; ++i) {
    fprintf(f, "%24.16e\n", grid->grid_rad_coord[i]);
  }

  fprintf(f, "grid_rad_weight\n");
  for (uint64_t i=0 ; i<size_grid_rad_weight ; ++i) {
    fprintf(f, "%24.16e\n", grid->grid_rad_weight[i]);
  }

  fclose(f);
  grid->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_ao (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  ao_t* ao = file->ao;
  if (ao == NULL) return TREXIO_SUCCESS;

  if (ao->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(ao->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_ao_shell %u\n", ao->rank_ao_shell);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_shell = 0;
  if (ao->rank_ao_shell != 0) size_ao_shell = 1;

  for (unsigned int i=0; i<ao->rank_ao_shell; ++i){
    fprintf(f, "dims_ao_shell %u %" PRIu64 "\n", i, ao->dims_ao_shell[i]);
    size_ao_shell *= ao->dims_ao_shell[i];
  }
  fprintf(f, "rank_ao_normalization %u\n", ao->rank_ao_normalization);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_normalization = 0;
  if (ao->rank_ao_normalization != 0) size_ao_normalization = 1;

  for (unsigned int i=0; i<ao->rank_ao_normalization; ++i){
    fprintf(f, "dims_ao_normalization %u %" PRIu64 "\n", i, ao->dims_ao_normalization[i]);
    size_ao_normalization *= ao->dims_ao_normalization[i];
  }

  fprintf(f, "ao_cartesian_isSet %u \n", ao->ao_cartesian_isSet);
  if (ao->ao_cartesian_isSet == true) fprintf(f, "ao_cartesian %" PRId64 " \n", ao->ao_cartesian);
  fprintf(f, "ao_num_isSet %u \n", ao->ao_num_isSet);
  if (ao->ao_num_isSet == true) fprintf(f, "ao_num %" PRId64 " \n", ao->ao_num);


  /* Write arrays */

  fprintf(f, "ao_shell\n");
  for (uint64_t i=0 ; i<size_ao_shell ; ++i) {
    fprintf(f, "%" PRId64 "\n", ao->ao_shell[i]);
  }

  fprintf(f, "ao_normalization\n");
  for (uint64_t i=0 ; i<size_ao_normalization ; ++i) {
    fprintf(f, "%24.16e\n", ao->ao_normalization[i]);
  }

  fclose(f);
  ao->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_ao_1e_int (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* ao_1e_int = file->ao_1e_int;
  if (ao_1e_int == NULL) return TREXIO_SUCCESS;

  if (ao_1e_int->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(ao_1e_int->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_ao_1e_int_overlap %u\n", ao_1e_int->rank_ao_1e_int_overlap);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_overlap = 0;
  if (ao_1e_int->rank_ao_1e_int_overlap != 0) size_ao_1e_int_overlap = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_overlap; ++i){
    fprintf(f, "dims_ao_1e_int_overlap %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_overlap[i]);
    size_ao_1e_int_overlap *= ao_1e_int->dims_ao_1e_int_overlap[i];
  }
  fprintf(f, "rank_ao_1e_int_kinetic %u\n", ao_1e_int->rank_ao_1e_int_kinetic);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_kinetic = 0;
  if (ao_1e_int->rank_ao_1e_int_kinetic != 0) size_ao_1e_int_kinetic = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_kinetic; ++i){
    fprintf(f, "dims_ao_1e_int_kinetic %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_kinetic[i]);
    size_ao_1e_int_kinetic *= ao_1e_int->dims_ao_1e_int_kinetic[i];
  }
  fprintf(f, "rank_ao_1e_int_potential_n_e %u\n", ao_1e_int->rank_ao_1e_int_potential_n_e);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_potential_n_e = 0;
  if (ao_1e_int->rank_ao_1e_int_potential_n_e != 0) size_ao_1e_int_potential_n_e = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_potential_n_e; ++i){
    fprintf(f, "dims_ao_1e_int_potential_n_e %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_potential_n_e[i]);
    size_ao_1e_int_potential_n_e *= ao_1e_int->dims_ao_1e_int_potential_n_e[i];
  }
  fprintf(f, "rank_ao_1e_int_ecp %u\n", ao_1e_int->rank_ao_1e_int_ecp);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_ecp = 0;
  if (ao_1e_int->rank_ao_1e_int_ecp != 0) size_ao_1e_int_ecp = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_ecp; ++i){
    fprintf(f, "dims_ao_1e_int_ecp %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_ecp[i]);
    size_ao_1e_int_ecp *= ao_1e_int->dims_ao_1e_int_ecp[i];
  }
  fprintf(f, "rank_ao_1e_int_core_hamiltonian %u\n", ao_1e_int->rank_ao_1e_int_core_hamiltonian);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_core_hamiltonian = 0;
  if (ao_1e_int->rank_ao_1e_int_core_hamiltonian != 0) size_ao_1e_int_core_hamiltonian = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_core_hamiltonian; ++i){
    fprintf(f, "dims_ao_1e_int_core_hamiltonian %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_core_hamiltonian[i]);
    size_ao_1e_int_core_hamiltonian *= ao_1e_int->dims_ao_1e_int_core_hamiltonian[i];
  }
  fprintf(f, "rank_ao_1e_int_overlap_im %u\n", ao_1e_int->rank_ao_1e_int_overlap_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_overlap_im = 0;
  if (ao_1e_int->rank_ao_1e_int_overlap_im != 0) size_ao_1e_int_overlap_im = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_overlap_im; ++i){
    fprintf(f, "dims_ao_1e_int_overlap_im %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_overlap_im[i]);
    size_ao_1e_int_overlap_im *= ao_1e_int->dims_ao_1e_int_overlap_im[i];
  }
  fprintf(f, "rank_ao_1e_int_kinetic_im %u\n", ao_1e_int->rank_ao_1e_int_kinetic_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_kinetic_im = 0;
  if (ao_1e_int->rank_ao_1e_int_kinetic_im != 0) size_ao_1e_int_kinetic_im = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_kinetic_im; ++i){
    fprintf(f, "dims_ao_1e_int_kinetic_im %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_kinetic_im[i]);
    size_ao_1e_int_kinetic_im *= ao_1e_int->dims_ao_1e_int_kinetic_im[i];
  }
  fprintf(f, "rank_ao_1e_int_potential_n_e_im %u\n", ao_1e_int->rank_ao_1e_int_potential_n_e_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_potential_n_e_im = 0;
  if (ao_1e_int->rank_ao_1e_int_potential_n_e_im != 0) size_ao_1e_int_potential_n_e_im = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_potential_n_e_im; ++i){
    fprintf(f, "dims_ao_1e_int_potential_n_e_im %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_potential_n_e_im[i]);
    size_ao_1e_int_potential_n_e_im *= ao_1e_int->dims_ao_1e_int_potential_n_e_im[i];
  }
  fprintf(f, "rank_ao_1e_int_ecp_im %u\n", ao_1e_int->rank_ao_1e_int_ecp_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_ecp_im = 0;
  if (ao_1e_int->rank_ao_1e_int_ecp_im != 0) size_ao_1e_int_ecp_im = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_ecp_im; ++i){
    fprintf(f, "dims_ao_1e_int_ecp_im %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_ecp_im[i]);
    size_ao_1e_int_ecp_im *= ao_1e_int->dims_ao_1e_int_ecp_im[i];
  }
  fprintf(f, "rank_ao_1e_int_core_hamiltonian_im %u\n", ao_1e_int->rank_ao_1e_int_core_hamiltonian_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_ao_1e_int_core_hamiltonian_im = 0;
  if (ao_1e_int->rank_ao_1e_int_core_hamiltonian_im != 0) size_ao_1e_int_core_hamiltonian_im = 1;

  for (unsigned int i=0; i<ao_1e_int->rank_ao_1e_int_core_hamiltonian_im; ++i){
    fprintf(f, "dims_ao_1e_int_core_hamiltonian_im %u %" PRIu64 "\n", i, ao_1e_int->dims_ao_1e_int_core_hamiltonian_im[i]);
    size_ao_1e_int_core_hamiltonian_im *= ao_1e_int->dims_ao_1e_int_core_hamiltonian_im[i];
  }



  /* Write arrays */

  fprintf(f, "ao_1e_int_overlap\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_overlap ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_overlap[i]);
  }

  fprintf(f, "ao_1e_int_kinetic\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_kinetic ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_kinetic[i]);
  }

  fprintf(f, "ao_1e_int_potential_n_e\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_potential_n_e ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_potential_n_e[i]);
  }

  fprintf(f, "ao_1e_int_ecp\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_ecp ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_ecp[i]);
  }

  fprintf(f, "ao_1e_int_core_hamiltonian\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_core_hamiltonian ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_core_hamiltonian[i]);
  }

  fprintf(f, "ao_1e_int_overlap_im\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_overlap_im ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_overlap_im[i]);
  }

  fprintf(f, "ao_1e_int_kinetic_im\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_kinetic_im ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_kinetic_im[i]);
  }

  fprintf(f, "ao_1e_int_potential_n_e_im\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_potential_n_e_im ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_potential_n_e_im[i]);
  }

  fprintf(f, "ao_1e_int_ecp_im\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_ecp_im ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_ecp_im[i]);
  }

  fprintf(f, "ao_1e_int_core_hamiltonian_im\n");
  for (uint64_t i=0 ; i<size_ao_1e_int_core_hamiltonian_im ; ++i) {
    fprintf(f, "%24.16e\n", ao_1e_int->ao_1e_int_core_hamiltonian_im[i]);
  }

  fclose(f);
  ao_1e_int->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_ao_2e_int (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  ao_2e_int_t* ao_2e_int = file->ao_2e_int;
  if (ao_2e_int == NULL) return TREXIO_SUCCESS;

  if (ao_2e_int->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(ao_2e_int->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */

  fprintf(f, "ao_2e_int_eri_cholesky_num_isSet %u \n", ao_2e_int->ao_2e_int_eri_cholesky_num_isSet);
  if (ao_2e_int->ao_2e_int_eri_cholesky_num_isSet == true) fprintf(f, "ao_2e_int_eri_cholesky_num %" PRId64 " \n", ao_2e_int->ao_2e_int_eri_cholesky_num);
  fprintf(f, "ao_2e_int_eri_lr_cholesky_num_isSet %u \n", ao_2e_int->ao_2e_int_eri_lr_cholesky_num_isSet);
  if (ao_2e_int->ao_2e_int_eri_lr_cholesky_num_isSet == true) fprintf(f, "ao_2e_int_eri_lr_cholesky_num %" PRId64 " \n", ao_2e_int->ao_2e_int_eri_lr_cholesky_num);


  /* Write arrays */

  fclose(f);
  ao_2e_int->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_mo (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  mo_t* mo = file->mo;
  if (mo == NULL) return TREXIO_SUCCESS;

  if (mo->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(mo->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_mo_coefficient %u\n", mo->rank_mo_coefficient);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_coefficient = 0;
  if (mo->rank_mo_coefficient != 0) size_mo_coefficient = 1;

  for (unsigned int i=0; i<mo->rank_mo_coefficient; ++i){
    fprintf(f, "dims_mo_coefficient %u %" PRIu64 "\n", i, mo->dims_mo_coefficient[i]);
    size_mo_coefficient *= mo->dims_mo_coefficient[i];
  }
  fprintf(f, "rank_mo_coefficient_im %u\n", mo->rank_mo_coefficient_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_coefficient_im = 0;
  if (mo->rank_mo_coefficient_im != 0) size_mo_coefficient_im = 1;

  for (unsigned int i=0; i<mo->rank_mo_coefficient_im; ++i){
    fprintf(f, "dims_mo_coefficient_im %u %" PRIu64 "\n", i, mo->dims_mo_coefficient_im[i]);
    size_mo_coefficient_im *= mo->dims_mo_coefficient_im[i];
  }
  fprintf(f, "rank_mo_occupation %u\n", mo->rank_mo_occupation);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_occupation = 0;
  if (mo->rank_mo_occupation != 0) size_mo_occupation = 1;

  for (unsigned int i=0; i<mo->rank_mo_occupation; ++i){
    fprintf(f, "dims_mo_occupation %u %" PRIu64 "\n", i, mo->dims_mo_occupation[i]);
    size_mo_occupation *= mo->dims_mo_occupation[i];
  }
  fprintf(f, "rank_mo_energy %u\n", mo->rank_mo_energy);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_energy = 0;
  if (mo->rank_mo_energy != 0) size_mo_energy = 1;

  for (unsigned int i=0; i<mo->rank_mo_energy; ++i){
    fprintf(f, "dims_mo_energy %u %" PRIu64 "\n", i, mo->dims_mo_energy[i]);
    size_mo_energy *= mo->dims_mo_energy[i];
  }
  fprintf(f, "rank_mo_spin %u\n", mo->rank_mo_spin);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_spin = 0;
  if (mo->rank_mo_spin != 0) size_mo_spin = 1;

  for (unsigned int i=0; i<mo->rank_mo_spin; ++i){
    fprintf(f, "dims_mo_spin %u %" PRIu64 "\n", i, mo->dims_mo_spin[i]);
    size_mo_spin *= mo->dims_mo_spin[i];
  }
  fprintf(f, "rank_mo_k_point %u\n", mo->rank_mo_k_point);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_k_point = 0;
  if (mo->rank_mo_k_point != 0) size_mo_k_point = 1;

  for (unsigned int i=0; i<mo->rank_mo_k_point; ++i){
    fprintf(f, "dims_mo_k_point %u %" PRIu64 "\n", i, mo->dims_mo_k_point[i]);
    size_mo_k_point *= mo->dims_mo_k_point[i];
  }
  fprintf(f, "rank_mo_class %u\n", mo->rank_mo_class);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_class = 0;
  if (mo->rank_mo_class != 0) size_mo_class = 1;

  for (unsigned int i=0; i<mo->rank_mo_class; ++i){
    fprintf(f, "dims_mo_class %u %" PRIu64 "\n", i, mo->dims_mo_class[i]);
    size_mo_class *= mo->dims_mo_class[i];
  }
  fprintf(f, "rank_mo_symmetry %u\n", mo->rank_mo_symmetry);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_symmetry = 0;
  if (mo->rank_mo_symmetry != 0) size_mo_symmetry = 1;

  for (unsigned int i=0; i<mo->rank_mo_symmetry; ++i){
    fprintf(f, "dims_mo_symmetry %u %" PRIu64 "\n", i, mo->dims_mo_symmetry[i]);
    size_mo_symmetry *= mo->dims_mo_symmetry[i];
  }

  fprintf(f, "mo_num_isSet %u \n", mo->mo_num_isSet);
  if (mo->mo_num_isSet == true) fprintf(f, "mo_num %" PRId64 " \n", mo->mo_num);

  fprintf(f, "len_mo_type %" PRIu64 "\n", mo->len_mo_type);
  fprintf(f, "mo_type\n");
  if (mo->len_mo_type != 0) fprintf(f, "%s\n", mo->mo_type);

  /* Write arrays */

  fprintf(f, "mo_coefficient\n");
  for (uint64_t i=0 ; i<size_mo_coefficient ; ++i) {
    fprintf(f, "%24.16e\n", mo->mo_coefficient[i]);
  }

  fprintf(f, "mo_coefficient_im\n");
  for (uint64_t i=0 ; i<size_mo_coefficient_im ; ++i) {
    fprintf(f, "%24.16e\n", mo->mo_coefficient_im[i]);
  }

  fprintf(f, "mo_occupation\n");
  for (uint64_t i=0 ; i<size_mo_occupation ; ++i) {
    fprintf(f, "%24.16e\n", mo->mo_occupation[i]);
  }

  fprintf(f, "mo_energy\n");
  for (uint64_t i=0 ; i<size_mo_energy ; ++i) {
    fprintf(f, "%24.16e\n", mo->mo_energy[i]);
  }

  fprintf(f, "mo_spin\n");
  for (uint64_t i=0 ; i<size_mo_spin ; ++i) {
    fprintf(f, "%" PRId64 "\n", mo->mo_spin[i]);
  }

  fprintf(f, "mo_k_point\n");
  for (uint64_t i=0 ; i<size_mo_k_point ; ++i) {
    fprintf(f, "%" PRId64 "\n", mo->mo_k_point[i]);
  }

  fprintf(f, "mo_class\n");
  for (uint64_t i=0 ; i<size_mo_class ; ++i) {
    fprintf(f, "%s\n", mo->mo_class[i]);
  }

  fprintf(f, "mo_symmetry\n");
  for (uint64_t i=0 ; i<size_mo_symmetry ; ++i) {
    fprintf(f, "%s\n", mo->mo_symmetry[i]);
  }

  fclose(f);
  mo->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_mo_1e_int (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* mo_1e_int = file->mo_1e_int;
  if (mo_1e_int == NULL) return TREXIO_SUCCESS;

  if (mo_1e_int->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(mo_1e_int->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_mo_1e_int_overlap %u\n", mo_1e_int->rank_mo_1e_int_overlap);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_overlap = 0;
  if (mo_1e_int->rank_mo_1e_int_overlap != 0) size_mo_1e_int_overlap = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_overlap; ++i){
    fprintf(f, "dims_mo_1e_int_overlap %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_overlap[i]);
    size_mo_1e_int_overlap *= mo_1e_int->dims_mo_1e_int_overlap[i];
  }
  fprintf(f, "rank_mo_1e_int_kinetic %u\n", mo_1e_int->rank_mo_1e_int_kinetic);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_kinetic = 0;
  if (mo_1e_int->rank_mo_1e_int_kinetic != 0) size_mo_1e_int_kinetic = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_kinetic; ++i){
    fprintf(f, "dims_mo_1e_int_kinetic %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_kinetic[i]);
    size_mo_1e_int_kinetic *= mo_1e_int->dims_mo_1e_int_kinetic[i];
  }
  fprintf(f, "rank_mo_1e_int_potential_n_e %u\n", mo_1e_int->rank_mo_1e_int_potential_n_e);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_potential_n_e = 0;
  if (mo_1e_int->rank_mo_1e_int_potential_n_e != 0) size_mo_1e_int_potential_n_e = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_potential_n_e; ++i){
    fprintf(f, "dims_mo_1e_int_potential_n_e %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_potential_n_e[i]);
    size_mo_1e_int_potential_n_e *= mo_1e_int->dims_mo_1e_int_potential_n_e[i];
  }
  fprintf(f, "rank_mo_1e_int_ecp %u\n", mo_1e_int->rank_mo_1e_int_ecp);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_ecp = 0;
  if (mo_1e_int->rank_mo_1e_int_ecp != 0) size_mo_1e_int_ecp = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_ecp; ++i){
    fprintf(f, "dims_mo_1e_int_ecp %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_ecp[i]);
    size_mo_1e_int_ecp *= mo_1e_int->dims_mo_1e_int_ecp[i];
  }
  fprintf(f, "rank_mo_1e_int_core_hamiltonian %u\n", mo_1e_int->rank_mo_1e_int_core_hamiltonian);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_core_hamiltonian = 0;
  if (mo_1e_int->rank_mo_1e_int_core_hamiltonian != 0) size_mo_1e_int_core_hamiltonian = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_core_hamiltonian; ++i){
    fprintf(f, "dims_mo_1e_int_core_hamiltonian %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_core_hamiltonian[i]);
    size_mo_1e_int_core_hamiltonian *= mo_1e_int->dims_mo_1e_int_core_hamiltonian[i];
  }
  fprintf(f, "rank_mo_1e_int_overlap_im %u\n", mo_1e_int->rank_mo_1e_int_overlap_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_overlap_im = 0;
  if (mo_1e_int->rank_mo_1e_int_overlap_im != 0) size_mo_1e_int_overlap_im = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_overlap_im; ++i){
    fprintf(f, "dims_mo_1e_int_overlap_im %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_overlap_im[i]);
    size_mo_1e_int_overlap_im *= mo_1e_int->dims_mo_1e_int_overlap_im[i];
  }
  fprintf(f, "rank_mo_1e_int_kinetic_im %u\n", mo_1e_int->rank_mo_1e_int_kinetic_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_kinetic_im = 0;
  if (mo_1e_int->rank_mo_1e_int_kinetic_im != 0) size_mo_1e_int_kinetic_im = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_kinetic_im; ++i){
    fprintf(f, "dims_mo_1e_int_kinetic_im %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_kinetic_im[i]);
    size_mo_1e_int_kinetic_im *= mo_1e_int->dims_mo_1e_int_kinetic_im[i];
  }
  fprintf(f, "rank_mo_1e_int_potential_n_e_im %u\n", mo_1e_int->rank_mo_1e_int_potential_n_e_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_potential_n_e_im = 0;
  if (mo_1e_int->rank_mo_1e_int_potential_n_e_im != 0) size_mo_1e_int_potential_n_e_im = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_potential_n_e_im; ++i){
    fprintf(f, "dims_mo_1e_int_potential_n_e_im %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_potential_n_e_im[i]);
    size_mo_1e_int_potential_n_e_im *= mo_1e_int->dims_mo_1e_int_potential_n_e_im[i];
  }
  fprintf(f, "rank_mo_1e_int_ecp_im %u\n", mo_1e_int->rank_mo_1e_int_ecp_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_ecp_im = 0;
  if (mo_1e_int->rank_mo_1e_int_ecp_im != 0) size_mo_1e_int_ecp_im = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_ecp_im; ++i){
    fprintf(f, "dims_mo_1e_int_ecp_im %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_ecp_im[i]);
    size_mo_1e_int_ecp_im *= mo_1e_int->dims_mo_1e_int_ecp_im[i];
  }
  fprintf(f, "rank_mo_1e_int_core_hamiltonian_im %u\n", mo_1e_int->rank_mo_1e_int_core_hamiltonian_im);
  // workaround for the case of missing blocks in the file
  uint64_t size_mo_1e_int_core_hamiltonian_im = 0;
  if (mo_1e_int->rank_mo_1e_int_core_hamiltonian_im != 0) size_mo_1e_int_core_hamiltonian_im = 1;

  for (unsigned int i=0; i<mo_1e_int->rank_mo_1e_int_core_hamiltonian_im; ++i){
    fprintf(f, "dims_mo_1e_int_core_hamiltonian_im %u %" PRIu64 "\n", i, mo_1e_int->dims_mo_1e_int_core_hamiltonian_im[i]);
    size_mo_1e_int_core_hamiltonian_im *= mo_1e_int->dims_mo_1e_int_core_hamiltonian_im[i];
  }



  /* Write arrays */

  fprintf(f, "mo_1e_int_overlap\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_overlap ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_overlap[i]);
  }

  fprintf(f, "mo_1e_int_kinetic\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_kinetic ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_kinetic[i]);
  }

  fprintf(f, "mo_1e_int_potential_n_e\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_potential_n_e ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_potential_n_e[i]);
  }

  fprintf(f, "mo_1e_int_ecp\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_ecp ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_ecp[i]);
  }

  fprintf(f, "mo_1e_int_core_hamiltonian\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_core_hamiltonian ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_core_hamiltonian[i]);
  }

  fprintf(f, "mo_1e_int_overlap_im\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_overlap_im ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_overlap_im[i]);
  }

  fprintf(f, "mo_1e_int_kinetic_im\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_kinetic_im ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_kinetic_im[i]);
  }

  fprintf(f, "mo_1e_int_potential_n_e_im\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_potential_n_e_im ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_potential_n_e_im[i]);
  }

  fprintf(f, "mo_1e_int_ecp_im\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_ecp_im ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_ecp_im[i]);
  }

  fprintf(f, "mo_1e_int_core_hamiltonian_im\n");
  for (uint64_t i=0 ; i<size_mo_1e_int_core_hamiltonian_im ; ++i) {
    fprintf(f, "%24.16e\n", mo_1e_int->mo_1e_int_core_hamiltonian_im[i]);
  }

  fclose(f);
  mo_1e_int->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_mo_2e_int (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  mo_2e_int_t* mo_2e_int = file->mo_2e_int;
  if (mo_2e_int == NULL) return TREXIO_SUCCESS;

  if (mo_2e_int->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(mo_2e_int->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */

  fprintf(f, "mo_2e_int_eri_cholesky_num_isSet %u \n", mo_2e_int->mo_2e_int_eri_cholesky_num_isSet);
  if (mo_2e_int->mo_2e_int_eri_cholesky_num_isSet == true) fprintf(f, "mo_2e_int_eri_cholesky_num %" PRId64 " \n", mo_2e_int->mo_2e_int_eri_cholesky_num);
  fprintf(f, "mo_2e_int_eri_lr_cholesky_num_isSet %u \n", mo_2e_int->mo_2e_int_eri_lr_cholesky_num_isSet);
  if (mo_2e_int->mo_2e_int_eri_lr_cholesky_num_isSet == true) fprintf(f, "mo_2e_int_eri_lr_cholesky_num %" PRId64 " \n", mo_2e_int->mo_2e_int_eri_lr_cholesky_num);


  /* Write arrays */

  fclose(f);
  mo_2e_int->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_determinant (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  determinant_t* determinant = file->determinant;
  if (determinant == NULL) return TREXIO_SUCCESS;

  if (determinant->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(determinant->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */

  fprintf(f, "determinant_num_isSet %u \n", determinant->determinant_num_isSet);
  if (determinant->determinant_num_isSet == true) fprintf(f, "determinant_num %" PRId64 " \n", determinant->determinant_num);


  /* Write arrays */

  fclose(f);
  determinant->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_csf (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  csf_t* csf = file->csf;
  if (csf == NULL) return TREXIO_SUCCESS;

  if (csf->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(csf->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */

  fprintf(f, "csf_num_isSet %u \n", csf->csf_num_isSet);
  if (csf->csf_num_isSet == true) fprintf(f, "csf_num %" PRId64 " \n", csf->csf_num);


  /* Write arrays */

  fclose(f);
  csf->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_amplitude (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  amplitude_t* amplitude = file->amplitude;
  if (amplitude == NULL) return TREXIO_SUCCESS;

  if (amplitude->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(amplitude->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */



  /* Write arrays */

  fclose(f);
  amplitude->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_rdm (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  rdm_t* rdm = file->rdm;
  if (rdm == NULL) return TREXIO_SUCCESS;

  if (rdm->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(rdm->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_rdm_1e %u\n", rdm->rank_rdm_1e);
  // workaround for the case of missing blocks in the file
  uint64_t size_rdm_1e = 0;
  if (rdm->rank_rdm_1e != 0) size_rdm_1e = 1;

  for (unsigned int i=0; i<rdm->rank_rdm_1e; ++i){
    fprintf(f, "dims_rdm_1e %u %" PRIu64 "\n", i, rdm->dims_rdm_1e[i]);
    size_rdm_1e *= rdm->dims_rdm_1e[i];
  }
  fprintf(f, "rank_rdm_1e_up %u\n", rdm->rank_rdm_1e_up);
  // workaround for the case of missing blocks in the file
  uint64_t size_rdm_1e_up = 0;
  if (rdm->rank_rdm_1e_up != 0) size_rdm_1e_up = 1;

  for (unsigned int i=0; i<rdm->rank_rdm_1e_up; ++i){
    fprintf(f, "dims_rdm_1e_up %u %" PRIu64 "\n", i, rdm->dims_rdm_1e_up[i]);
    size_rdm_1e_up *= rdm->dims_rdm_1e_up[i];
  }
  fprintf(f, "rank_rdm_1e_dn %u\n", rdm->rank_rdm_1e_dn);
  // workaround for the case of missing blocks in the file
  uint64_t size_rdm_1e_dn = 0;
  if (rdm->rank_rdm_1e_dn != 0) size_rdm_1e_dn = 1;

  for (unsigned int i=0; i<rdm->rank_rdm_1e_dn; ++i){
    fprintf(f, "dims_rdm_1e_dn %u %" PRIu64 "\n", i, rdm->dims_rdm_1e_dn[i]);
    size_rdm_1e_dn *= rdm->dims_rdm_1e_dn[i];
  }
  fprintf(f, "rank_rdm_1e_transition %u\n", rdm->rank_rdm_1e_transition);
  // workaround for the case of missing blocks in the file
  uint64_t size_rdm_1e_transition = 0;
  if (rdm->rank_rdm_1e_transition != 0) size_rdm_1e_transition = 1;

  for (unsigned int i=0; i<rdm->rank_rdm_1e_transition; ++i){
    fprintf(f, "dims_rdm_1e_transition %u %" PRIu64 "\n", i, rdm->dims_rdm_1e_transition[i]);
    size_rdm_1e_transition *= rdm->dims_rdm_1e_transition[i];
  }

  fprintf(f, "rdm_2e_cholesky_num_isSet %u \n", rdm->rdm_2e_cholesky_num_isSet);
  if (rdm->rdm_2e_cholesky_num_isSet == true) fprintf(f, "rdm_2e_cholesky_num %" PRId64 " \n", rdm->rdm_2e_cholesky_num);
  fprintf(f, "rdm_2e_upup_cholesky_num_isSet %u \n", rdm->rdm_2e_upup_cholesky_num_isSet);
  if (rdm->rdm_2e_upup_cholesky_num_isSet == true) fprintf(f, "rdm_2e_upup_cholesky_num %" PRId64 " \n", rdm->rdm_2e_upup_cholesky_num);
  fprintf(f, "rdm_2e_dndn_cholesky_num_isSet %u \n", rdm->rdm_2e_dndn_cholesky_num_isSet);
  if (rdm->rdm_2e_dndn_cholesky_num_isSet == true) fprintf(f, "rdm_2e_dndn_cholesky_num %" PRId64 " \n", rdm->rdm_2e_dndn_cholesky_num);
  fprintf(f, "rdm_2e_updn_cholesky_num_isSet %u \n", rdm->rdm_2e_updn_cholesky_num_isSet);
  if (rdm->rdm_2e_updn_cholesky_num_isSet == true) fprintf(f, "rdm_2e_updn_cholesky_num %" PRId64 " \n", rdm->rdm_2e_updn_cholesky_num);


  /* Write arrays */

  fprintf(f, "rdm_1e\n");
  for (uint64_t i=0 ; i<size_rdm_1e ; ++i) {
    fprintf(f, "%24.16e\n", rdm->rdm_1e[i]);
  }

  fprintf(f, "rdm_1e_up\n");
  for (uint64_t i=0 ; i<size_rdm_1e_up ; ++i) {
    fprintf(f, "%24.16e\n", rdm->rdm_1e_up[i]);
  }

  fprintf(f, "rdm_1e_dn\n");
  for (uint64_t i=0 ; i<size_rdm_1e_dn ; ++i) {
    fprintf(f, "%24.16e\n", rdm->rdm_1e_dn[i]);
  }

  fprintf(f, "rdm_1e_transition\n");
  for (uint64_t i=0 ; i<size_rdm_1e_transition ; ++i) {
    fprintf(f, "%24.16e\n", rdm->rdm_1e_transition[i]);
  }

  fclose(f);
  rdm->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_jastrow (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  jastrow_t* jastrow = file->jastrow;
  if (jastrow == NULL) return TREXIO_SUCCESS;

  if (jastrow->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(jastrow->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_jastrow_en %u\n", jastrow->rank_jastrow_en);
  // workaround for the case of missing blocks in the file
  uint64_t size_jastrow_en = 0;
  if (jastrow->rank_jastrow_en != 0) size_jastrow_en = 1;

  for (unsigned int i=0; i<jastrow->rank_jastrow_en; ++i){
    fprintf(f, "dims_jastrow_en %u %" PRIu64 "\n", i, jastrow->dims_jastrow_en[i]);
    size_jastrow_en *= jastrow->dims_jastrow_en[i];
  }
  fprintf(f, "rank_jastrow_ee %u\n", jastrow->rank_jastrow_ee);
  // workaround for the case of missing blocks in the file
  uint64_t size_jastrow_ee = 0;
  if (jastrow->rank_jastrow_ee != 0) size_jastrow_ee = 1;

  for (unsigned int i=0; i<jastrow->rank_jastrow_ee; ++i){
    fprintf(f, "dims_jastrow_ee %u %" PRIu64 "\n", i, jastrow->dims_jastrow_ee[i]);
    size_jastrow_ee *= jastrow->dims_jastrow_ee[i];
  }
  fprintf(f, "rank_jastrow_een %u\n", jastrow->rank_jastrow_een);
  // workaround for the case of missing blocks in the file
  uint64_t size_jastrow_een = 0;
  if (jastrow->rank_jastrow_een != 0) size_jastrow_een = 1;

  for (unsigned int i=0; i<jastrow->rank_jastrow_een; ++i){
    fprintf(f, "dims_jastrow_een %u %" PRIu64 "\n", i, jastrow->dims_jastrow_een[i]);
    size_jastrow_een *= jastrow->dims_jastrow_een[i];
  }
  fprintf(f, "rank_jastrow_en_nucleus %u\n", jastrow->rank_jastrow_en_nucleus);
  // workaround for the case of missing blocks in the file
  uint64_t size_jastrow_en_nucleus = 0;
  if (jastrow->rank_jastrow_en_nucleus != 0) size_jastrow_en_nucleus = 1;

  for (unsigned int i=0; i<jastrow->rank_jastrow_en_nucleus; ++i){
    fprintf(f, "dims_jastrow_en_nucleus %u %" PRIu64 "\n", i, jastrow->dims_jastrow_en_nucleus[i]);
    size_jastrow_en_nucleus *= jastrow->dims_jastrow_en_nucleus[i];
  }
  fprintf(f, "rank_jastrow_een_nucleus %u\n", jastrow->rank_jastrow_een_nucleus);
  // workaround for the case of missing blocks in the file
  uint64_t size_jastrow_een_nucleus = 0;
  if (jastrow->rank_jastrow_een_nucleus != 0) size_jastrow_een_nucleus = 1;

  for (unsigned int i=0; i<jastrow->rank_jastrow_een_nucleus; ++i){
    fprintf(f, "dims_jastrow_een_nucleus %u %" PRIu64 "\n", i, jastrow->dims_jastrow_een_nucleus[i]);
    size_jastrow_een_nucleus *= jastrow->dims_jastrow_een_nucleus[i];
  }
  fprintf(f, "rank_jastrow_en_scaling %u\n", jastrow->rank_jastrow_en_scaling);
  // workaround for the case of missing blocks in the file
  uint64_t size_jastrow_en_scaling = 0;
  if (jastrow->rank_jastrow_en_scaling != 0) size_jastrow_en_scaling = 1;

  for (unsigned int i=0; i<jastrow->rank_jastrow_en_scaling; ++i){
    fprintf(f, "dims_jastrow_en_scaling %u %" PRIu64 "\n", i, jastrow->dims_jastrow_en_scaling[i]);
    size_jastrow_en_scaling *= jastrow->dims_jastrow_en_scaling[i];
  }

  fprintf(f, "jastrow_en_num_isSet %u \n", jastrow->jastrow_en_num_isSet);
  if (jastrow->jastrow_en_num_isSet == true) fprintf(f, "jastrow_en_num %" PRId64 " \n", jastrow->jastrow_en_num);
  fprintf(f, "jastrow_ee_num_isSet %u \n", jastrow->jastrow_ee_num_isSet);
  if (jastrow->jastrow_ee_num_isSet == true) fprintf(f, "jastrow_ee_num %" PRId64 " \n", jastrow->jastrow_ee_num);
  fprintf(f, "jastrow_een_num_isSet %u \n", jastrow->jastrow_een_num_isSet);
  if (jastrow->jastrow_een_num_isSet == true) fprintf(f, "jastrow_een_num %" PRId64 " \n", jastrow->jastrow_een_num);
  fprintf(f, "jastrow_ee_scaling_isSet %u \n", jastrow->jastrow_ee_scaling_isSet);
  if (jastrow->jastrow_ee_scaling_isSet == true) fprintf(f, "jastrow_ee_scaling %24.16e \n", jastrow->jastrow_ee_scaling);

  fprintf(f, "len_jastrow_type %" PRIu64 "\n", jastrow->len_jastrow_type);
  fprintf(f, "jastrow_type\n");
  if (jastrow->len_jastrow_type != 0) fprintf(f, "%s\n", jastrow->jastrow_type);

  /* Write arrays */

  fprintf(f, "jastrow_en\n");
  for (uint64_t i=0 ; i<size_jastrow_en ; ++i) {
    fprintf(f, "%24.16e\n", jastrow->jastrow_en[i]);
  }

  fprintf(f, "jastrow_ee\n");
  for (uint64_t i=0 ; i<size_jastrow_ee ; ++i) {
    fprintf(f, "%24.16e\n", jastrow->jastrow_ee[i]);
  }

  fprintf(f, "jastrow_een\n");
  for (uint64_t i=0 ; i<size_jastrow_een ; ++i) {
    fprintf(f, "%24.16e\n", jastrow->jastrow_een[i]);
  }

  fprintf(f, "jastrow_en_nucleus\n");
  for (uint64_t i=0 ; i<size_jastrow_en_nucleus ; ++i) {
    fprintf(f, "%" PRId64 "\n", jastrow->jastrow_en_nucleus[i]);
  }

  fprintf(f, "jastrow_een_nucleus\n");
  for (uint64_t i=0 ; i<size_jastrow_een_nucleus ; ++i) {
    fprintf(f, "%" PRId64 "\n", jastrow->jastrow_een_nucleus[i]);
  }

  fprintf(f, "jastrow_en_scaling\n");
  for (uint64_t i=0 ; i<size_jastrow_en_scaling ; ++i) {
    fprintf(f, "%24.16e\n", jastrow->jastrow_en_scaling[i]);
  }

  fclose(f);
  jastrow->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_flush_qmc (trexio_text_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  qmc_t* qmc = file->qmc;
  if (qmc == NULL) return TREXIO_SUCCESS;

  if (qmc->to_flush == 0) return TREXIO_SUCCESS;

  assert (file->parent.mode == 'w' || file->parent.mode == 'u');

  FILE* f = fopen(qmc->file_name, "w");
  if (f == NULL) return TREXIO_INVALID_ARG_1;

  /* Write the dimensioning variables */
  fprintf(f, "rank_qmc_point %u\n", qmc->rank_qmc_point);
  // workaround for the case of missing blocks in the file
  uint64_t size_qmc_point = 0;
  if (qmc->rank_qmc_point != 0) size_qmc_point = 1;

  for (unsigned int i=0; i<qmc->rank_qmc_point; ++i){
    fprintf(f, "dims_qmc_point %u %" PRIu64 "\n", i, qmc->dims_qmc_point[i]);
    size_qmc_point *= qmc->dims_qmc_point[i];
  }
  fprintf(f, "rank_qmc_psi %u\n", qmc->rank_qmc_psi);
  // workaround for the case of missing blocks in the file
  uint64_t size_qmc_psi = 0;
  if (qmc->rank_qmc_psi != 0) size_qmc_psi = 1;

  for (unsigned int i=0; i<qmc->rank_qmc_psi; ++i){
    fprintf(f, "dims_qmc_psi %u %" PRIu64 "\n", i, qmc->dims_qmc_psi[i]);
    size_qmc_psi *= qmc->dims_qmc_psi[i];
  }
  fprintf(f, "rank_qmc_e_loc %u\n", qmc->rank_qmc_e_loc);
  // workaround for the case of missing blocks in the file
  uint64_t size_qmc_e_loc = 0;
  if (qmc->rank_qmc_e_loc != 0) size_qmc_e_loc = 1;

  for (unsigned int i=0; i<qmc->rank_qmc_e_loc; ++i){
    fprintf(f, "dims_qmc_e_loc %u %" PRIu64 "\n", i, qmc->dims_qmc_e_loc[i]);
    size_qmc_e_loc *= qmc->dims_qmc_e_loc[i];
  }

  fprintf(f, "qmc_num_isSet %u \n", qmc->qmc_num_isSet);
  if (qmc->qmc_num_isSet == true) fprintf(f, "qmc_num %" PRId64 " \n", qmc->qmc_num);


  /* Write arrays */

  fprintf(f, "qmc_point\n");
  for (uint64_t i=0 ; i<size_qmc_point ; ++i) {
    fprintf(f, "%24.16e\n", qmc->qmc_point[i]);
  }

  fprintf(f, "qmc_psi\n");
  for (uint64_t i=0 ; i<size_qmc_psi ; ++i) {
    fprintf(f, "%24.16e\n", qmc->qmc_psi[i]);
  }

  fprintf(f, "qmc_e_loc\n");
  for (uint64_t i=0 ; i<size_qmc_e_loc ; ++i) {
    fprintf(f, "%24.16e\n", qmc->qmc_e_loc[i]);
  }

  fclose(f);
  qmc->to_flush = 0;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_delete_metadata (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  metadata_t* metadata = trexio_text_read_metadata(f);
  if (metadata == NULL) return TREXIO_FAILURE;

  int rc = remove(metadata->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  metadata->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_metadata(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_nucleus (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  nucleus_t* nucleus = trexio_text_read_nucleus(f);
  if (nucleus == NULL) return TREXIO_FAILURE;

  int rc = remove(nucleus->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  nucleus->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_nucleus(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_cell (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  cell_t* cell = trexio_text_read_cell(f);
  if (cell == NULL) return TREXIO_FAILURE;

  int rc = remove(cell->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  cell->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_cell(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_pbc (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  pbc_t* pbc = trexio_text_read_pbc(f);
  if (pbc == NULL) return TREXIO_FAILURE;

  int rc = remove(pbc->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  pbc->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_pbc(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_electron (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  electron_t* electron = trexio_text_read_electron(f);
  if (electron == NULL) return TREXIO_FAILURE;

  int rc = remove(electron->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  electron->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_electron(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_state (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  state_t* state = trexio_text_read_state(f);
  if (state == NULL) return TREXIO_FAILURE;

  int rc = remove(state->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  state->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_state(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_basis (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  basis_t* basis = trexio_text_read_basis(f);
  if (basis == NULL) return TREXIO_FAILURE;

  int rc = remove(basis->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  basis->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_basis(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_ecp (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  ecp_t* ecp = trexio_text_read_ecp(f);
  if (ecp == NULL) return TREXIO_FAILURE;

  int rc = remove(ecp->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  ecp->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_ecp(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_grid (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  grid_t* grid = trexio_text_read_grid(f);
  if (grid == NULL) return TREXIO_FAILURE;

  int rc = remove(grid->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  grid->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_grid(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_ao (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  ao_t* ao = trexio_text_read_ao(f);
  if (ao == NULL) return TREXIO_FAILURE;

  int rc = remove(ao->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  ao->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_ao(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_ao_1e_int (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  ao_1e_int_t* ao_1e_int = trexio_text_read_ao_1e_int(f);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  int rc = remove(ao_1e_int->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  ao_1e_int->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_ao_1e_int(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_ao_2e_int (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  ao_2e_int_t* ao_2e_int = trexio_text_read_ao_2e_int(f);
  if (ao_2e_int == NULL) return TREXIO_FAILURE;

  int rc = remove(ao_2e_int->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  ao_2e_int->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_ao_2e_int(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_mo (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  mo_t* mo = trexio_text_read_mo(f);
  if (mo == NULL) return TREXIO_FAILURE;

  int rc = remove(mo->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  mo->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_mo(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_mo_1e_int (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  mo_1e_int_t* mo_1e_int = trexio_text_read_mo_1e_int(f);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  int rc = remove(mo_1e_int->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  mo_1e_int->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_mo_1e_int(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_mo_2e_int (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  mo_2e_int_t* mo_2e_int = trexio_text_read_mo_2e_int(f);
  if (mo_2e_int == NULL) return TREXIO_FAILURE;

  int rc = remove(mo_2e_int->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  mo_2e_int->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_mo_2e_int(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_determinant (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  determinant_t* determinant = trexio_text_read_determinant(f);
  if (determinant == NULL) return TREXIO_FAILURE;

  int rc = remove(determinant->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  determinant->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_determinant(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_csf (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  csf_t* csf = trexio_text_read_csf(f);
  if (csf == NULL) return TREXIO_FAILURE;

  int rc = remove(csf->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  csf->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_csf(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_amplitude (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  amplitude_t* amplitude = trexio_text_read_amplitude(f);
  if (amplitude == NULL) return TREXIO_FAILURE;

  int rc = remove(amplitude->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  amplitude->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_amplitude(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_rdm (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  rdm_t* rdm = trexio_text_read_rdm(f);
  if (rdm == NULL) return TREXIO_FAILURE;

  int rc = remove(rdm->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  rdm->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_rdm(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_jastrow (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  jastrow_t* jastrow = trexio_text_read_jastrow(f);
  if (jastrow == NULL) return TREXIO_FAILURE;

  int rc = remove(jastrow->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  jastrow->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_jastrow(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_delete_qmc (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  qmc_t* qmc = trexio_text_read_qmc(f);
  if (qmc == NULL) return TREXIO_FAILURE;

  int rc = remove(qmc->file_name);
  if (rc == -1) return TREXIO_FAILURE;

  qmc->to_flush = 0;

  trexio_exit_code rc_free = trexio_text_free_qmc(f);
  if (rc_free != TREXIO_SUCCESS) return rc_free;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_has_nucleus_charge (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->rank_nucleus_charge > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_nucleus_coord (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->rank_nucleus_coord > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_cell_a (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->rank_cell_a > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_cell_b (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->rank_cell_b > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_cell_c (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->rank_cell_c > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_cell_g_a (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->rank_cell_g_a > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_cell_g_b (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->rank_cell_g_b > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_cell_g_c (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->rank_cell_g_c > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_pbc_k_point (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  pbc_t* const pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (pbc->rank_pbc_k_point > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_pbc_k_point_weight (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  pbc_t* const pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (pbc->rank_pbc_k_point_weight > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_nucleus_index (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_nucleus_index > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_shell_ang_mom (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_shell_ang_mom > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_shell_factor (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_shell_factor > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_r_power (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_r_power > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_nao_grid_start (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_nao_grid_start > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_nao_grid_size (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_nao_grid_size > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_shell_index (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_shell_index > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_exponent (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_exponent > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_exponent_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_exponent_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_coefficient (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_coefficient > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_coefficient_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_coefficient_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_oscillation_arg (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_oscillation_arg > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_prim_factor (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_prim_factor > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_nao_grid_radius (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_nao_grid_radius > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_nao_grid_phi (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_nao_grid_phi > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_nao_grid_grad (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_nao_grid_grad > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_nao_grid_lap (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_nao_grid_lap > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_interpolator_phi (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_interpolator_phi > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_interpolator_grad (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_interpolator_grad > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_interpolator_lap (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->rank_basis_interpolator_lap > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ecp_max_ang_mom_plus_1 (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->rank_ecp_max_ang_mom_plus_1 > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ecp_z_core (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->rank_ecp_z_core > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ecp_ang_mom (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->rank_ecp_ang_mom > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ecp_nucleus_index (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->rank_ecp_nucleus_index > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ecp_exponent (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->rank_ecp_exponent > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ecp_coefficient (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->rank_ecp_coefficient > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ecp_power (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->rank_ecp_power > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_coord (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->rank_grid_coord > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_weight (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->rank_grid_weight > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_ang_coord (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->rank_grid_ang_coord > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_ang_weight (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->rank_grid_ang_weight > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_rad_coord (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->rank_grid_rad_coord > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_rad_weight (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->rank_grid_rad_weight > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_shell (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_t* const ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  if (ao->rank_ao_shell > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_normalization (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_t* const ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  if (ao->rank_ao_normalization > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_overlap (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_overlap > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_kinetic (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_kinetic > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_potential_n_e (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_potential_n_e > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_ecp (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_ecp > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_core_hamiltonian (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_core_hamiltonian > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_overlap_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_overlap_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_kinetic_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_kinetic_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_potential_n_e_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_potential_n_e_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_ecp_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_ecp_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_1e_int_core_hamiltonian_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->rank_ao_1e_int_core_hamiltonian_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_coefficient (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->rank_mo_coefficient > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_coefficient_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->rank_mo_coefficient_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_occupation (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->rank_mo_occupation > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_energy (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->rank_mo_energy > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_spin (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->rank_mo_spin > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_k_point (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->rank_mo_k_point > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_overlap (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_overlap > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_kinetic (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_kinetic > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_potential_n_e (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_potential_n_e > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_ecp (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_ecp > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_core_hamiltonian (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_core_hamiltonian > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_overlap_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_overlap_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_kinetic_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_kinetic_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_potential_n_e_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_potential_n_e_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_ecp_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_ecp_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_1e_int_core_hamiltonian_im (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->rank_mo_1e_int_core_hamiltonian_im > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_rdm_1e (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rank_rdm_1e > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_rdm_1e_up (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rank_rdm_1e_up > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_rdm_1e_dn (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rank_rdm_1e_dn > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_rdm_1e_transition (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rank_rdm_1e_transition > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_en (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->rank_jastrow_en > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_ee (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->rank_jastrow_ee > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_een (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->rank_jastrow_een > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_en_nucleus (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->rank_jastrow_en_nucleus > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_een_nucleus (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->rank_jastrow_een_nucleus > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_en_scaling (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->rank_jastrow_en_scaling > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_qmc_point (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (qmc->rank_qmc_point > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_qmc_psi (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (qmc->rank_qmc_psi > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_qmc_e_loc (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (qmc->rank_qmc_e_loc > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_metadata_code (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->rank_metadata_code > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_metadata_author (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->rank_metadata_author > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_nucleus_label (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->rank_nucleus_label > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_state_label (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->rank_state_label > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_state_file_name (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->rank_state_file_name > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_class (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->rank_mo_class > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_symmetry (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->rank_mo_symmetry > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code trexio_text_has_ao_2e_int_eri(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_file_name[] = "/ao_2e_int_eri.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_ao_2e_int_eri_lr(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_lr.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_lr_file_name[] = "/ao_2e_int_eri_lr.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_lr_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_lr_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_ao_2e_int_eri_cholesky(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_cholesky_file_name[] = "/ao_2e_int_eri_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_cholesky_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_ao_2e_int_eri_lr_cholesky(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_lr_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_lr_cholesky_file_name[] = "/ao_2e_int_eri_lr_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_lr_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_lr_cholesky_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_mo_2e_int_eri(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_file_name[] = "/mo_2e_int_eri.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_mo_2e_int_eri_lr(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_lr.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_lr_file_name[] = "/mo_2e_int_eri_lr.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_lr_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_lr_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_mo_2e_int_eri_cholesky(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_cholesky_file_name[] = "/mo_2e_int_eri_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_cholesky_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_mo_2e_int_eri_lr_cholesky(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_lr_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_lr_cholesky_file_name[] = "/mo_2e_int_eri_lr_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_lr_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_lr_cholesky_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_csf_det_coefficient(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The csf_det_coefficient.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char csf_det_coefficient_file_name[] = "/csf_det_coefficient.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, csf_det_coefficient_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(csf_det_coefficient_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_amplitude_single(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_single.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_single_file_name[] = "/amplitude_single.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_single_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_single_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_amplitude_single_exp(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_single_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_single_exp_file_name[] = "/amplitude_single_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_single_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_single_exp_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_amplitude_double(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_double.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_double_file_name[] = "/amplitude_double.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_double_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_double_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_amplitude_double_exp(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_double_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_double_exp_file_name[] = "/amplitude_double_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_double_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_double_exp_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_amplitude_triple(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_triple.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_triple_file_name[] = "/amplitude_triple.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_triple_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_triple_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_amplitude_triple_exp(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_triple_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_triple_exp_file_name[] = "/amplitude_triple_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_triple_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_triple_exp_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_amplitude_quadruple(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_quadruple.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_quadruple_file_name[] = "/amplitude_quadruple.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_quadruple_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_quadruple_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_amplitude_quadruple_exp(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_quadruple_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_quadruple_exp_file_name[] = "/amplitude_quadruple_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_quadruple_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_quadruple_exp_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_file_name[] = "/rdm_2e.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e_upup(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_upup.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_upup_file_name[] = "/rdm_2e_upup.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_upup_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_upup_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e_dndn(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_dndn.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_dndn_file_name[] = "/rdm_2e_dndn.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_dndn_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_dndn_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e_updn(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_updn.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_updn_file_name[] = "/rdm_2e_updn.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_updn_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_updn_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e_transition(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_transition.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_transition_file_name[] = "/rdm_2e_transition.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_transition_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_transition_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e_cholesky(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_cholesky_file_name[] = "/rdm_2e_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_cholesky_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e_upup_cholesky(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_upup_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_upup_cholesky_file_name[] = "/rdm_2e_upup_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_upup_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_upup_cholesky_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e_dndn_cholesky(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_dndn_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_dndn_cholesky_file_name[] = "/rdm_2e_dndn_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_dndn_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_dndn_cholesky_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_rdm_2e_updn_cholesky(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_updn_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_updn_cholesky_file_name[] = "/rdm_2e_updn_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_updn_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_updn_cholesky_file_name));

  /* Check the return code of access function to determine whether the file with sparse data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_has_metadata_code_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->metadata_code_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_metadata_author_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->metadata_author_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_metadata_unsafe (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->metadata_unsafe_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_nucleus_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->nucleus_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_nucleus_repulsion (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->nucleus_repulsion_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_cell_two_pi (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  cell_t* cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->cell_two_pi_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_pbc_periodic (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (pbc->pbc_periodic_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_pbc_k_point_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (pbc->pbc_k_point_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_pbc_madelung (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (pbc->pbc_madelung_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_electron_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  if (electron->electron_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_electron_up_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  if (electron->electron_up_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_electron_dn_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  if (electron->electron_dn_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_state_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->state_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_state_id (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->state_id_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_state_energy (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->state_energy_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_prim_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_prim_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_shell_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_shell_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_nao_grid_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_nao_grid_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_interp_coeff_cnt (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_interp_coeff_cnt_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_e_cut (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_e_cut_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ecp_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->ecp_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_rad_precision (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_rad_precision_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_max_ang_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_max_ang_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_min_ang_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_min_ang_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_ang_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_ang_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_rad_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_rad_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_cartesian (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_t* ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  if (ao->ao_cartesian_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_t* ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  if (ao->ao_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_2e_int_eri_cholesky_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_2e_int_t* ao_2e_int = trexio_text_read_ao_2e_int((trexio_text_t*) file);
  if (ao_2e_int == NULL) return TREXIO_FAILURE;

  if (ao_2e_int->ao_2e_int_eri_cholesky_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  ao_2e_int_t* ao_2e_int = trexio_text_read_ao_2e_int((trexio_text_t*) file);
  if (ao_2e_int == NULL) return TREXIO_FAILURE;

  if (ao_2e_int->ao_2e_int_eri_lr_cholesky_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_2e_int_eri_cholesky_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_2e_int_t* mo_2e_int = trexio_text_read_mo_2e_int((trexio_text_t*) file);
  if (mo_2e_int == NULL) return TREXIO_FAILURE;

  if (mo_2e_int->mo_2e_int_eri_cholesky_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_2e_int_t* mo_2e_int = trexio_text_read_mo_2e_int((trexio_text_t*) file);
  if (mo_2e_int == NULL) return TREXIO_FAILURE;

  if (mo_2e_int->mo_2e_int_eri_lr_cholesky_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_determinant_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  determinant_t* determinant = trexio_text_read_determinant((trexio_text_t*) file);
  if (determinant == NULL) return TREXIO_FAILURE;

  if (determinant->determinant_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_csf_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  csf_t* csf = trexio_text_read_csf((trexio_text_t*) file);
  if (csf == NULL) return TREXIO_FAILURE;

  if (csf->csf_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_rdm_2e_cholesky_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rdm_2e_cholesky_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_rdm_2e_upup_cholesky_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rdm_2e_upup_cholesky_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_rdm_2e_dndn_cholesky_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rdm_2e_dndn_cholesky_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_rdm_2e_updn_cholesky_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rdm_2e_updn_cholesky_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_en_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_en_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_ee_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_ee_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_een_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_een_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_ee_scaling (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_ee_scaling_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_qmc_num (trexio_t* const file)
{
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  qmc_t* qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (qmc->qmc_num_isSet == true){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_metadata_package_version (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->len_metadata_package_version > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_metadata_description (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->len_metadata_description > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_nucleus_point_group (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->len_nucleus_point_group > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_state_current_label (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->len_state_current_label > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_type (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->len_basis_type > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_oscillation_kind (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->len_basis_oscillation_kind > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_basis_interpolator_kind (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->len_basis_interpolator_kind > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_grid_description (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->len_grid_description > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_mo_type (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->len_mo_type > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_text_has_jastrow_type (trexio_t* const file)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->len_jastrow_type > 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code trexio_text_has_determinant_coefficient(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const char file_name[] = "/determinant_coefficient.txt";

  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(file_name));

  /* Check the return code of access function to determine whether the file with data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_text_has_csf_coefficient(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const char file_name[] = "/csf_coefficient.txt";

  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(file_name));

  /* Check the return code of access function to determine whether the file with data exists or not */
  if (access(file_full_path, F_OK) == 0){
    return TREXIO_SUCCESS;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_text_read_nucleus_charge (trexio_t* const file, double* const nucleus_charge,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_charge == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (rank != nucleus->rank_nucleus_charge) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != nucleus->dims_nucleus_charge[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    nucleus_charge[i] = nucleus->nucleus_charge[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_nucleus_coord (trexio_t* const file, double* const nucleus_coord,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (rank != nucleus->rank_nucleus_coord) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != nucleus->dims_nucleus_coord[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    nucleus_coord[i] = nucleus->nucleus_coord[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_cell_a (trexio_t* const file, double* const cell_a,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_a == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (rank != cell->rank_cell_a) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != cell->dims_cell_a[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell_a[i] = cell->cell_a[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_cell_b (trexio_t* const file, double* const cell_b,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_b == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (rank != cell->rank_cell_b) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != cell->dims_cell_b[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell_b[i] = cell->cell_b[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_cell_c (trexio_t* const file, double* const cell_c,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_c == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (rank != cell->rank_cell_c) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != cell->dims_cell_c[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell_c[i] = cell->cell_c[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_cell_g_a (trexio_t* const file, double* const cell_g_a,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_a == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (rank != cell->rank_cell_g_a) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != cell->dims_cell_g_a[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell_g_a[i] = cell->cell_g_a[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_cell_g_b (trexio_t* const file, double* const cell_g_b,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_b == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (rank != cell->rank_cell_g_b) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != cell->dims_cell_g_b[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell_g_b[i] = cell->cell_g_b[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_cell_g_c (trexio_t* const file, double* const cell_g_c,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_c == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (rank != cell->rank_cell_g_c) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != cell->dims_cell_g_c[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell_g_c[i] = cell->cell_g_c[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_pbc_k_point (trexio_t* const file, double* const pbc_k_point,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (pbc_k_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  pbc_t* const pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (rank != pbc->rank_pbc_k_point) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != pbc->dims_pbc_k_point[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    pbc_k_point[i] = pbc->pbc_k_point[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_pbc_k_point_weight (trexio_t* const file, double* const pbc_k_point_weight,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (pbc_k_point_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  pbc_t* const pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (rank != pbc->rank_pbc_k_point_weight) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != pbc->dims_pbc_k_point_weight[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    pbc_k_point_weight[i] = pbc->pbc_k_point_weight[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_nucleus_index (trexio_t* const file, int64_t* const basis_nucleus_index,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nucleus_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_nucleus_index) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_nucleus_index[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_nucleus_index[i] = basis->basis_nucleus_index[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_shell_ang_mom (trexio_t* const file, int64_t* const basis_shell_ang_mom,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_ang_mom == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_shell_ang_mom) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_shell_ang_mom[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_shell_ang_mom[i] = basis->basis_shell_ang_mom[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_shell_factor (trexio_t* const file, double* const basis_shell_factor,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_factor == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_shell_factor) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_shell_factor[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_shell_factor[i] = basis->basis_shell_factor[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_r_power (trexio_t* const file, int64_t* const basis_r_power,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_r_power == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_r_power) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_r_power[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_r_power[i] = basis->basis_r_power[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_nao_grid_start (trexio_t* const file, int64_t* const basis_nao_grid_start,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_start == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_nao_grid_start) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_nao_grid_start[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_nao_grid_start[i] = basis->basis_nao_grid_start[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_nao_grid_size (trexio_t* const file, int64_t* const basis_nao_grid_size,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_size == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_nao_grid_size) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_nao_grid_size[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_nao_grid_size[i] = basis->basis_nao_grid_size[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_shell_index (trexio_t* const file, int64_t* const basis_shell_index,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_shell_index) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_shell_index[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_shell_index[i] = basis->basis_shell_index[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_exponent (trexio_t* const file, double* const basis_exponent,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_exponent == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_exponent) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_exponent[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_exponent[i] = basis->basis_exponent[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_exponent_im (trexio_t* const file, double* const basis_exponent_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_exponent_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_exponent_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_exponent_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_exponent_im[i] = basis->basis_exponent_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_coefficient (trexio_t* const file, double* const basis_coefficient,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_coefficient) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_coefficient[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_coefficient[i] = basis->basis_coefficient[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_coefficient_im (trexio_t* const file, double* const basis_coefficient_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_coefficient_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_coefficient_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_coefficient_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_coefficient_im[i] = basis->basis_coefficient_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_oscillation_arg (trexio_t* const file, double* const basis_oscillation_arg,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_oscillation_arg == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_oscillation_arg) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_oscillation_arg[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_oscillation_arg[i] = basis->basis_oscillation_arg[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_prim_factor (trexio_t* const file, double* const basis_prim_factor,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_prim_factor == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_prim_factor) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_prim_factor[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_prim_factor[i] = basis->basis_prim_factor[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_nao_grid_radius (trexio_t* const file, double* const basis_nao_grid_radius,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_radius == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_nao_grid_radius) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_nao_grid_radius[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_nao_grid_radius[i] = basis->basis_nao_grid_radius[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_nao_grid_phi (trexio_t* const file, double* const basis_nao_grid_phi,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_phi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_nao_grid_phi) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_nao_grid_phi[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_nao_grid_phi[i] = basis->basis_nao_grid_phi[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_nao_grid_grad (trexio_t* const file, double* const basis_nao_grid_grad,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_grad == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_nao_grid_grad) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_nao_grid_grad[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_nao_grid_grad[i] = basis->basis_nao_grid_grad[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_nao_grid_lap (trexio_t* const file, double* const basis_nao_grid_lap,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_lap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_nao_grid_lap) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_nao_grid_lap[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_nao_grid_lap[i] = basis->basis_nao_grid_lap[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_interpolator_phi (trexio_t* const file, double* const basis_interpolator_phi,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_phi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_interpolator_phi) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_interpolator_phi[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_interpolator_phi[i] = basis->basis_interpolator_phi[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_interpolator_grad (trexio_t* const file, double* const basis_interpolator_grad,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_grad == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_interpolator_grad) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_interpolator_grad[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_interpolator_grad[i] = basis->basis_interpolator_grad[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_interpolator_lap (trexio_t* const file, double* const basis_interpolator_lap,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_lap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (rank != basis->rank_basis_interpolator_lap) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != basis->dims_basis_interpolator_lap[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis_interpolator_lap[i] = basis->basis_interpolator_lap[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ecp_max_ang_mom_plus_1 (trexio_t* const file, int64_t* const ecp_max_ang_mom_plus_1,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_max_ang_mom_plus_1 == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_max_ang_mom_plus_1) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ecp->dims_ecp_max_ang_mom_plus_1[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp_max_ang_mom_plus_1[i] = ecp->ecp_max_ang_mom_plus_1[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ecp_z_core (trexio_t* const file, int64_t* const ecp_z_core,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_z_core == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_z_core) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ecp->dims_ecp_z_core[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp_z_core[i] = ecp->ecp_z_core[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ecp_ang_mom (trexio_t* const file, int64_t* const ecp_ang_mom,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_ang_mom == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_ang_mom) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ecp->dims_ecp_ang_mom[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp_ang_mom[i] = ecp->ecp_ang_mom[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ecp_nucleus_index (trexio_t* const file, int64_t* const ecp_nucleus_index,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_nucleus_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_nucleus_index) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ecp->dims_ecp_nucleus_index[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp_nucleus_index[i] = ecp->ecp_nucleus_index[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ecp_exponent (trexio_t* const file, double* const ecp_exponent,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_exponent == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_exponent) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ecp->dims_ecp_exponent[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp_exponent[i] = ecp->ecp_exponent[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ecp_coefficient (trexio_t* const file, double* const ecp_coefficient,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_coefficient) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ecp->dims_ecp_coefficient[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp_coefficient[i] = ecp->ecp_coefficient[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ecp_power (trexio_t* const file, int64_t* const ecp_power,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_power == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_power) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ecp->dims_ecp_power[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp_power[i] = ecp->ecp_power[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_coord (trexio_t* const file, double* const grid_coord,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (rank != grid->rank_grid_coord) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != grid->dims_grid_coord[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid_coord[i] = grid->grid_coord[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_weight (trexio_t* const file, double* const grid_weight,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (rank != grid->rank_grid_weight) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != grid->dims_grid_weight[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid_weight[i] = grid->grid_weight[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_ang_coord (trexio_t* const file, double* const grid_ang_coord,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_ang_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (rank != grid->rank_grid_ang_coord) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != grid->dims_grid_ang_coord[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid_ang_coord[i] = grid->grid_ang_coord[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_ang_weight (trexio_t* const file, double* const grid_ang_weight,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_ang_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (rank != grid->rank_grid_ang_weight) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != grid->dims_grid_ang_weight[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid_ang_weight[i] = grid->grid_ang_weight[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_rad_coord (trexio_t* const file, double* const grid_rad_coord,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_rad_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (rank != grid->rank_grid_rad_coord) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != grid->dims_grid_rad_coord[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid_rad_coord[i] = grid->grid_rad_coord[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_rad_weight (trexio_t* const file, double* const grid_rad_weight,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_rad_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (rank != grid->rank_grid_rad_weight) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != grid->dims_grid_rad_weight[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid_rad_weight[i] = grid->grid_rad_weight[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_shell (trexio_t* const file, int64_t* const ao_shell,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_shell == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_t* const ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  if (rank != ao->rank_ao_shell) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao->dims_ao_shell[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_shell[i] = ao->ao_shell[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_normalization (trexio_t* const file, double* const ao_normalization,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_normalization == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_t* const ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  if (rank != ao->rank_ao_normalization) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao->dims_ao_normalization[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_normalization[i] = ao->ao_normalization[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_overlap (trexio_t* const file, double* const ao_1e_int_overlap,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_overlap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_overlap) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_overlap[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_overlap[i] = ao_1e_int->ao_1e_int_overlap[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_kinetic (trexio_t* const file, double* const ao_1e_int_kinetic,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_kinetic == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_kinetic) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_kinetic[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_kinetic[i] = ao_1e_int->ao_1e_int_kinetic[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_potential_n_e (trexio_t* const file, double* const ao_1e_int_potential_n_e,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_potential_n_e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_potential_n_e) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_potential_n_e[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_potential_n_e[i] = ao_1e_int->ao_1e_int_potential_n_e[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_ecp (trexio_t* const file, double* const ao_1e_int_ecp,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_ecp == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_ecp) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_ecp[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_ecp[i] = ao_1e_int->ao_1e_int_ecp[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_core_hamiltonian (trexio_t* const file, double* const ao_1e_int_core_hamiltonian,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_core_hamiltonian == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_core_hamiltonian) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_core_hamiltonian[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_core_hamiltonian[i] = ao_1e_int->ao_1e_int_core_hamiltonian[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_overlap_im (trexio_t* const file, double* const ao_1e_int_overlap_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_overlap_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_overlap_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_overlap_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_overlap_im[i] = ao_1e_int->ao_1e_int_overlap_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_kinetic_im (trexio_t* const file, double* const ao_1e_int_kinetic_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_kinetic_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_kinetic_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_kinetic_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_kinetic_im[i] = ao_1e_int->ao_1e_int_kinetic_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_potential_n_e_im (trexio_t* const file, double* const ao_1e_int_potential_n_e_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_potential_n_e_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_potential_n_e_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_potential_n_e_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_potential_n_e_im[i] = ao_1e_int->ao_1e_int_potential_n_e_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_ecp_im (trexio_t* const file, double* const ao_1e_int_ecp_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_ecp_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_ecp_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_ecp_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_ecp_im[i] = ao_1e_int->ao_1e_int_ecp_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_1e_int_core_hamiltonian_im (trexio_t* const file, double* const ao_1e_int_core_hamiltonian_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_core_hamiltonian_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != ao_1e_int->rank_ao_1e_int_core_hamiltonian_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != ao_1e_int->dims_ao_1e_int_core_hamiltonian_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int_core_hamiltonian_im[i] = ao_1e_int->ao_1e_int_core_hamiltonian_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_coefficient (trexio_t* const file, double* const mo_coefficient,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (rank != mo->rank_mo_coefficient) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo->dims_mo_coefficient[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_coefficient[i] = mo->mo_coefficient[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_coefficient_im (trexio_t* const file, double* const mo_coefficient_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_coefficient_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (rank != mo->rank_mo_coefficient_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo->dims_mo_coefficient_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_coefficient_im[i] = mo->mo_coefficient_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_occupation (trexio_t* const file, double* const mo_occupation,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_occupation == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (rank != mo->rank_mo_occupation) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo->dims_mo_occupation[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_occupation[i] = mo->mo_occupation[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_energy (trexio_t* const file, double* const mo_energy,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_energy == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (rank != mo->rank_mo_energy) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo->dims_mo_energy[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_energy[i] = mo->mo_energy[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_spin (trexio_t* const file, int64_t* const mo_spin,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_spin == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (rank != mo->rank_mo_spin) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo->dims_mo_spin[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_spin[i] = mo->mo_spin[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_k_point (trexio_t* const file, int64_t* const mo_k_point,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_k_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (rank != mo->rank_mo_k_point) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo->dims_mo_k_point[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_k_point[i] = mo->mo_k_point[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_overlap (trexio_t* const file, double* const mo_1e_int_overlap,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_overlap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_overlap) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_overlap[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_overlap[i] = mo_1e_int->mo_1e_int_overlap[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_kinetic (trexio_t* const file, double* const mo_1e_int_kinetic,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_kinetic == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_kinetic) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_kinetic[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_kinetic[i] = mo_1e_int->mo_1e_int_kinetic[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_potential_n_e (trexio_t* const file, double* const mo_1e_int_potential_n_e,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_potential_n_e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_potential_n_e) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_potential_n_e[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_potential_n_e[i] = mo_1e_int->mo_1e_int_potential_n_e[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_ecp (trexio_t* const file, double* const mo_1e_int_ecp,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_ecp == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_ecp) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_ecp[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_ecp[i] = mo_1e_int->mo_1e_int_ecp[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_core_hamiltonian (trexio_t* const file, double* const mo_1e_int_core_hamiltonian,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_core_hamiltonian == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_core_hamiltonian) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_core_hamiltonian[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_core_hamiltonian[i] = mo_1e_int->mo_1e_int_core_hamiltonian[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_overlap_im (trexio_t* const file, double* const mo_1e_int_overlap_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_overlap_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_overlap_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_overlap_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_overlap_im[i] = mo_1e_int->mo_1e_int_overlap_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_kinetic_im (trexio_t* const file, double* const mo_1e_int_kinetic_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_kinetic_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_kinetic_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_kinetic_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_kinetic_im[i] = mo_1e_int->mo_1e_int_kinetic_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_potential_n_e_im (trexio_t* const file, double* const mo_1e_int_potential_n_e_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_potential_n_e_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_potential_n_e_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_potential_n_e_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_potential_n_e_im[i] = mo_1e_int->mo_1e_int_potential_n_e_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_ecp_im (trexio_t* const file, double* const mo_1e_int_ecp_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_ecp_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_ecp_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_ecp_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_ecp_im[i] = mo_1e_int->mo_1e_int_ecp_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_1e_int_core_hamiltonian_im (trexio_t* const file, double* const mo_1e_int_core_hamiltonian_im,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_core_hamiltonian_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (rank != mo_1e_int->rank_mo_1e_int_core_hamiltonian_im) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != mo_1e_int->dims_mo_1e_int_core_hamiltonian_im[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int_core_hamiltonian_im[i] = mo_1e_int->mo_1e_int_core_hamiltonian_im[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_rdm_1e (trexio_t* const file, double* const rdm_1e,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rank != rdm->rank_rdm_1e) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != rdm->dims_rdm_1e[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    rdm_1e[i] = rdm->rdm_1e[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_rdm_1e_up (trexio_t* const file, double* const rdm_1e_up,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_up == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rank != rdm->rank_rdm_1e_up) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != rdm->dims_rdm_1e_up[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    rdm_1e_up[i] = rdm->rdm_1e_up[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_rdm_1e_dn (trexio_t* const file, double* const rdm_1e_dn,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_dn == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rank != rdm->rank_rdm_1e_dn) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != rdm->dims_rdm_1e_dn[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    rdm_1e_dn[i] = rdm->rdm_1e_dn[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_rdm_1e_transition (trexio_t* const file, double* const rdm_1e_transition,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_transition == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rank != rdm->rank_rdm_1e_transition) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != rdm->dims_rdm_1e_transition[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    rdm_1e_transition[i] = rdm->rdm_1e_transition[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_en (trexio_t* const file, double* const jastrow_en,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (rank != jastrow->rank_jastrow_en) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != jastrow->dims_jastrow_en[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow_en[i] = jastrow->jastrow_en[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_ee (trexio_t* const file, double* const jastrow_ee,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_ee == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (rank != jastrow->rank_jastrow_ee) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != jastrow->dims_jastrow_ee[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow_ee[i] = jastrow->jastrow_ee[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_een (trexio_t* const file, double* const jastrow_een,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_een == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (rank != jastrow->rank_jastrow_een) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != jastrow->dims_jastrow_een[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow_een[i] = jastrow->jastrow_een[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_en_nucleus (trexio_t* const file, int64_t* const jastrow_en_nucleus,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en_nucleus == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (rank != jastrow->rank_jastrow_en_nucleus) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != jastrow->dims_jastrow_en_nucleus[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow_en_nucleus[i] = jastrow->jastrow_en_nucleus[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_een_nucleus (trexio_t* const file, int64_t* const jastrow_een_nucleus,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_een_nucleus == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (rank != jastrow->rank_jastrow_een_nucleus) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != jastrow->dims_jastrow_een_nucleus[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow_een_nucleus[i] = jastrow->jastrow_een_nucleus[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_en_scaling (trexio_t* const file, double* const jastrow_en_scaling,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en_scaling == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (rank != jastrow->rank_jastrow_en_scaling) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != jastrow->dims_jastrow_en_scaling[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow_en_scaling[i] = jastrow->jastrow_en_scaling[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_qmc_point (trexio_t* const file, double* const qmc_point,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (rank != qmc->rank_qmc_point) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != qmc->dims_qmc_point[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    qmc_point[i] = qmc->qmc_point[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_qmc_psi (trexio_t* const file, double* const qmc_psi,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_psi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (rank != qmc->rank_qmc_psi) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != qmc->dims_qmc_psi[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    qmc_psi[i] = qmc->qmc_psi[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_qmc_e_loc (trexio_t* const file, double* const qmc_e_loc,
                               const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_e_loc == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (rank != qmc->rank_qmc_e_loc) return TREXIO_INVALID_ARG_3;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rank; ++i){
    if (dims[i] != qmc->dims_qmc_e_loc[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    qmc_e_loc[i] = qmc->qmc_e_loc[i];
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_metadata_code (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (dset == NULL) return TREXIO_INVALID_ARG_2;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (rank != metadata->rank_metadata_code) return TREXIO_INVALID_ARG_3;

  for (uint32_t i=0 ; i<rank ; ++i) {
    if (dims[i] != metadata->dims_metadata_code[i]) return TREXIO_INVALID_ARG_4;
  }

  strcpy(dset, "");
  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    strncat(dset, metadata->metadata_code[i], max_str_len);
    strcat(dset, TREXIO_DELIM);
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_metadata_author (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (dset == NULL) return TREXIO_INVALID_ARG_2;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (rank != metadata->rank_metadata_author) return TREXIO_INVALID_ARG_3;

  for (uint32_t i=0 ; i<rank ; ++i) {
    if (dims[i] != metadata->dims_metadata_author[i]) return TREXIO_INVALID_ARG_4;
  }

  strcpy(dset, "");
  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    strncat(dset, metadata->metadata_author[i], max_str_len);
    strcat(dset, TREXIO_DELIM);
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_nucleus_label (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (dset == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (rank != nucleus->rank_nucleus_label) return TREXIO_INVALID_ARG_3;

  for (uint32_t i=0 ; i<rank ; ++i) {
    if (dims[i] != nucleus->dims_nucleus_label[i]) return TREXIO_INVALID_ARG_4;
  }

  strcpy(dset, "");
  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    strncat(dset, nucleus->nucleus_label[i], max_str_len);
    strcat(dset, TREXIO_DELIM);
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_state_label (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (dset == NULL) return TREXIO_INVALID_ARG_2;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (rank != state->rank_state_label) return TREXIO_INVALID_ARG_3;

  for (uint32_t i=0 ; i<rank ; ++i) {
    if (dims[i] != state->dims_state_label[i]) return TREXIO_INVALID_ARG_4;
  }

  strcpy(dset, "");
  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    strncat(dset, state->state_label[i], max_str_len);
    strcat(dset, TREXIO_DELIM);
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_state_file_name (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (dset == NULL) return TREXIO_INVALID_ARG_2;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (rank != state->rank_state_file_name) return TREXIO_INVALID_ARG_3;

  for (uint32_t i=0 ; i<rank ; ++i) {
    if (dims[i] != state->dims_state_file_name[i]) return TREXIO_INVALID_ARG_4;
  }

  strcpy(dset, "");
  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    strncat(dset, state->state_file_name[i], max_str_len);
    strcat(dset, TREXIO_DELIM);
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_class (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (dset == NULL) return TREXIO_INVALID_ARG_2;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (rank != mo->rank_mo_class) return TREXIO_INVALID_ARG_3;

  for (uint32_t i=0 ; i<rank ; ++i) {
    if (dims[i] != mo->dims_mo_class[i]) return TREXIO_INVALID_ARG_4;
  }

  strcpy(dset, "");
  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    strncat(dset, mo->mo_class[i], max_str_len);
    strcat(dset, TREXIO_DELIM);
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_symmetry (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (dset == NULL) return TREXIO_INVALID_ARG_2;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (rank != mo->rank_mo_symmetry) return TREXIO_INVALID_ARG_3;

  for (uint32_t i=0 ; i<rank ; ++i) {
    if (dims[i] != mo->dims_mo_symmetry[i]) return TREXIO_INVALID_ARG_4;
  }

  strcpy(dset, "");
  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    strncat(dset, mo->mo_symmetry[i], max_str_len);
    strcat(dset, TREXIO_DELIM);
  }

  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_ao_2e_int_eri(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_file_name[] = "/ao_2e_int_eri.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_ao_2e_int_eri_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_file_name[] = "/ao_2e_int_eri.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_ao_2e_int_eri_lr(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_lr.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_lr_file_name[] = "/ao_2e_int_eri_lr.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_lr_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_lr_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_ao_2e_int_eri_lr_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_lr.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_lr_file_name[] = "/ao_2e_int_eri_lr.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_lr_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_lr_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_ao_2e_int_eri_cholesky(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_cholesky_file_name[] = "/ao_2e_int_eri_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
  } else {
    line_length = 58; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 3*i, index_sparse + 3*i + 1, index_sparse + 3*i + 2,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_ao_2e_int_eri_cholesky_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_cholesky_file_name[] = "/ao_2e_int_eri_cholesky.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_ao_2e_int_eri_lr_cholesky(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_lr_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_lr_cholesky_file_name[] = "/ao_2e_int_eri_lr_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_lr_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_lr_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
  } else {
    line_length = 58; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 3*i, index_sparse + 3*i + 1, index_sparse + 3*i + 2,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_ao_2e_int_eri_lr_cholesky_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The ao_2e_int_eri_lr_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char ao_2e_int_eri_lr_cholesky_file_name[] = "/ao_2e_int_eri_lr_cholesky.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_lr_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_lr_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_mo_2e_int_eri(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_file_name[] = "/mo_2e_int_eri.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_mo_2e_int_eri_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_file_name[] = "/mo_2e_int_eri.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_mo_2e_int_eri_lr(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_lr.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_lr_file_name[] = "/mo_2e_int_eri_lr.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_lr_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_lr_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_mo_2e_int_eri_lr_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_lr.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_lr_file_name[] = "/mo_2e_int_eri_lr.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_lr_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_lr_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_mo_2e_int_eri_cholesky(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_cholesky_file_name[] = "/mo_2e_int_eri_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
  } else {
    line_length = 58; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 3*i, index_sparse + 3*i + 1, index_sparse + 3*i + 2,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_mo_2e_int_eri_cholesky_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_cholesky_file_name[] = "/mo_2e_int_eri_cholesky.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_mo_2e_int_eri_lr_cholesky(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_lr_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_lr_cholesky_file_name[] = "/mo_2e_int_eri_lr_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_lr_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_lr_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
  } else {
    line_length = 58; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 3*i, index_sparse + 3*i + 1, index_sparse + 3*i + 2,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_mo_2e_int_eri_lr_cholesky_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The mo_2e_int_eri_lr_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char mo_2e_int_eri_lr_cholesky_file_name[] = "/mo_2e_int_eri_lr_cholesky.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_lr_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_lr_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_csf_det_coefficient(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The csf_det_coefficient.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char csf_det_coefficient_file_name[] = "/csf_det_coefficient.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, csf_det_coefficient_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(csf_det_coefficient_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 33; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 37; // 49 for 4 indices
  } else {
    line_length = 47; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 2*i, index_sparse + 2*i + 1,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_csf_det_coefficient_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The csf_det_coefficient.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char csf_det_coefficient_file_name[] = "/csf_det_coefficient.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, csf_det_coefficient_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(csf_det_coefficient_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_amplitude_single(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The amplitude_single.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_single_file_name[] = "/amplitude_single.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_single_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_single_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 33; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 37; // 49 for 4 indices
  } else {
    line_length = 47; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 2*i, index_sparse + 2*i + 1,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_amplitude_single_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_single.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_single_file_name[] = "/amplitude_single.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_single_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_single_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_amplitude_single_exp(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The amplitude_single_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_single_exp_file_name[] = "/amplitude_single_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_single_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_single_exp_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 33; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 37; // 49 for 4 indices
  } else {
    line_length = 47; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 2*i, index_sparse + 2*i + 1,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_amplitude_single_exp_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_single_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_single_exp_file_name[] = "/amplitude_single_exp.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_single_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_single_exp_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_amplitude_double(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The amplitude_double.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_double_file_name[] = "/amplitude_double.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_double_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_double_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_amplitude_double_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_double.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_double_file_name[] = "/amplitude_double.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_double_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_double_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_amplitude_double_exp(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The amplitude_double_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_double_exp_file_name[] = "/amplitude_double_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_double_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_double_exp_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_amplitude_double_exp_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_double_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_double_exp_file_name[] = "/amplitude_double_exp.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_double_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_double_exp_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_amplitude_triple(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The amplitude_triple.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_triple_file_name[] = "/amplitude_triple.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_triple_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_triple_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 49; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 61; // 49 for 4 indices
  } else {
    line_length = 91; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 6*i, index_sparse + 6*i + 1, index_sparse + 6*i + 2, index_sparse + 6*i + 3, index_sparse + 6*i + 4, index_sparse + 6*i + 5,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_amplitude_triple_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_triple.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_triple_file_name[] = "/amplitude_triple.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_triple_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_triple_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_amplitude_triple_exp(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The amplitude_triple_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_triple_exp_file_name[] = "/amplitude_triple_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_triple_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_triple_exp_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 49; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 61; // 49 for 4 indices
  } else {
    line_length = 91; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 6*i, index_sparse + 6*i + 1, index_sparse + 6*i + 2, index_sparse + 6*i + 3, index_sparse + 6*i + 4, index_sparse + 6*i + 5,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_amplitude_triple_exp_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_triple_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_triple_exp_file_name[] = "/amplitude_triple_exp.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_triple_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_triple_exp_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_amplitude_quadruple(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The amplitude_quadruple.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_quadruple_file_name[] = "/amplitude_quadruple.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_quadruple_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_quadruple_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 57; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 73; // 49 for 4 indices
  } else {
    line_length = 113; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 8*i, index_sparse + 8*i + 1, index_sparse + 8*i + 2, index_sparse + 8*i + 3, index_sparse + 8*i + 4, index_sparse + 8*i + 5, index_sparse + 8*i + 6, index_sparse + 8*i + 7,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_amplitude_quadruple_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_quadruple.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_quadruple_file_name[] = "/amplitude_quadruple.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_quadruple_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_quadruple_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_amplitude_quadruple_exp(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The amplitude_quadruple_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_quadruple_exp_file_name[] = "/amplitude_quadruple_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_quadruple_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_quadruple_exp_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 57; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 73; // 49 for 4 indices
  } else {
    line_length = 113; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 8*i, index_sparse + 8*i + 1, index_sparse + 8*i + 2, index_sparse + 8*i + 3, index_sparse + 8*i + 4, index_sparse + 8*i + 5, index_sparse + 8*i + 6, index_sparse + 8*i + 7,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_amplitude_quadruple_exp_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The amplitude_quadruple_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char amplitude_quadruple_exp_file_name[] = "/amplitude_quadruple_exp.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_quadruple_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_quadruple_exp_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_file_name[] = "/rdm_2e.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_file_name[] = "/rdm_2e.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e_upup(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e_upup.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_upup_file_name[] = "/rdm_2e_upup.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_upup_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_upup_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_upup_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_upup.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_upup_file_name[] = "/rdm_2e_upup.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_upup_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_upup_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e_dndn(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e_dndn.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_dndn_file_name[] = "/rdm_2e_dndn.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_dndn_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_dndn_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_dndn_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_dndn.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_dndn_file_name[] = "/rdm_2e_dndn.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_dndn_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_dndn_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e_updn(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e_updn.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_updn_file_name[] = "/rdm_2e_updn.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_updn_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_updn_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
  } else {
    line_length = 69; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 4*i, index_sparse + 4*i + 1, index_sparse + 4*i + 2, index_sparse + 4*i + 3,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_updn_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_updn.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_updn_file_name[] = "/rdm_2e_updn.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_updn_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_updn_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e_transition(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e_transition.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_transition_file_name[] = "/rdm_2e_transition.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_transition_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_transition_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 49; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 61; // 49 for 4 indices
  } else {
    line_length = 91; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 6*i, index_sparse + 6*i + 1, index_sparse + 6*i + 2, index_sparse + 6*i + 3, index_sparse + 6*i + 4, index_sparse + 6*i + 5,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_transition_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_transition.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_transition_file_name[] = "/rdm_2e_transition.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_transition_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_transition_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e_cholesky(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_cholesky_file_name[] = "/rdm_2e_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
  } else {
    line_length = 58; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 3*i, index_sparse + 3*i + 1, index_sparse + 3*i + 2,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_cholesky_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_cholesky_file_name[] = "/rdm_2e_cholesky.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e_upup_cholesky(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e_upup_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_upup_cholesky_file_name[] = "/rdm_2e_upup_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_upup_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_upup_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
  } else {
    line_length = 58; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 3*i, index_sparse + 3*i + 1, index_sparse + 3*i + 2,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_upup_cholesky_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_upup_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_upup_cholesky_file_name[] = "/rdm_2e_upup_cholesky.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_upup_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_upup_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e_dndn_cholesky(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e_dndn_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_dndn_cholesky_file_name[] = "/rdm_2e_dndn_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_dndn_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_dndn_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
  } else {
    line_length = 58; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 3*i, index_sparse + 3*i + 1, index_sparse + 3*i + 2,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_dndn_cholesky_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_dndn_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_dndn_cholesky_file_name[] = "/rdm_2e_dndn_cholesky.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_dndn_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_dndn_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_rdm_2e_updn_cholesky(trexio_t* const file,
                                               const int64_t offset_file,
                                               const int64_t size,
                                               const int64_t size_max,
                                               int64_t* const eof_read_size,
                                               int32_t* const index_sparse,
                                               double* const value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;

  /* Build the name of the file with sparse data.
     The rdm_2e_updn_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_updn_cholesky_file_name[] = "/rdm_2e_updn_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_updn_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_updn_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char
   */
  uint64_t line_length = 0UL;
  /* Determine the line length depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
  } else {
    line_length = 58; //69 for 4 indices
  }

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[1024];
  uint64_t count = 0UL;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {

      memset(buffer, 0, sizeof(buffer));

      if (fgets(buffer, 1023, f) == NULL){

        fclose(f);
        *eof_read_size = count;
        return TREXIO_END;

      } else {

        rc = sscanf(buffer, "%" SCNd32 " %" SCNd32 " %" SCNd32 " %lf",
                    index_sparse + 3*i, index_sparse + 3*i + 1, index_sparse + 3*i + 2,
                    value_sparse + i);
        if (rc <= 0) {
          fclose(f);
          return TREXIO_FAILURE;
        }
        count += 1UL;

      }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_rdm_2e_updn_cholesky_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data.
     The rdm_2e_updn_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed?
   */
  const char rdm_2e_updn_cholesky_file_name[] = "/rdm_2e_updn_cholesky.txt.size";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_updn_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_updn_cholesky_file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;


  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, offset_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64 " %" SCNd64 "", &size_item, &offset_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_metadata_package_version (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  strncpy(str, metadata->metadata_package_version, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_metadata_description (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  strncpy(str, metadata->metadata_description, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_nucleus_point_group (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  strncpy(str, nucleus->nucleus_point_group, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_state_current_label (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  strncpy(str, state->state_current_label, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_type (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  strncpy(str, basis->basis_type, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_oscillation_kind (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  strncpy(str, basis->basis_oscillation_kind, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_interpolator_kind (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  strncpy(str, basis->basis_interpolator_kind, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_description (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  strncpy(str, grid->grid_description, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_type (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  strncpy(str, mo->mo_type, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_type (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (str == NULL) return TREXIO_INVALID_ARG_2;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  strncpy(str, jastrow->jastrow_type, max_str_len);
  str[max_str_len-1] = '\0';

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_metadata_code_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  *num = metadata->metadata_code_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_metadata_author_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  *num = metadata->metadata_author_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_metadata_unsafe (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  *num = metadata->metadata_unsafe;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_nucleus_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  *num = nucleus->nucleus_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_nucleus_repulsion (trexio_t* const file, double* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  *num = nucleus->nucleus_repulsion;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_cell_two_pi (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  cell_t* cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  *num = cell->cell_two_pi;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_pbc_periodic (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  *num = pbc->pbc_periodic;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_pbc_k_point_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  *num = pbc->pbc_k_point_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_pbc_madelung (trexio_t* const file, double* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  *num = pbc->pbc_madelung;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_electron_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  *num = electron->electron_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_electron_up_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  *num = electron->electron_up_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_electron_dn_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  *num = electron->electron_dn_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_state_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  *num = state->state_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_state_id (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  *num = state->state_id;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_state_energy (trexio_t* const file, double* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  *num = state->state_energy;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_prim_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  *num = basis->basis_prim_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_shell_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  *num = basis->basis_shell_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_nao_grid_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  *num = basis->basis_nao_grid_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_interp_coeff_cnt (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  *num = basis->basis_interp_coeff_cnt;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_basis_e_cut (trexio_t* const file, double* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  *num = basis->basis_e_cut;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ecp_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  *num = ecp->ecp_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_rad_precision (trexio_t* const file, double* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  *num = grid->grid_rad_precision;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  *num = grid->grid_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_max_ang_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  *num = grid->grid_max_ang_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_min_ang_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  *num = grid->grid_min_ang_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_ang_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  *num = grid->grid_ang_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_grid_rad_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  *num = grid->grid_rad_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_cartesian (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  ao_t* ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  *num = ao->ao_cartesian;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  ao_t* ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  *num = ao->ao_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_2e_int_eri_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  ao_2e_int_t* ao_2e_int = trexio_text_read_ao_2e_int((trexio_text_t*) file);
  if (ao_2e_int == NULL) return TREXIO_FAILURE;

  *num = ao_2e_int->ao_2e_int_eri_cholesky_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  ao_2e_int_t* ao_2e_int = trexio_text_read_ao_2e_int((trexio_text_t*) file);
  if (ao_2e_int == NULL) return TREXIO_FAILURE;

  *num = ao_2e_int->ao_2e_int_eri_lr_cholesky_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  mo_t* mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  *num = mo->mo_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_2e_int_eri_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  mo_2e_int_t* mo_2e_int = trexio_text_read_mo_2e_int((trexio_text_t*) file);
  if (mo_2e_int == NULL) return TREXIO_FAILURE;

  *num = mo_2e_int->mo_2e_int_eri_cholesky_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  mo_2e_int_t* mo_2e_int = trexio_text_read_mo_2e_int((trexio_text_t*) file);
  if (mo_2e_int == NULL) return TREXIO_FAILURE;

  *num = mo_2e_int->mo_2e_int_eri_lr_cholesky_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_determinant_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  determinant_t* determinant = trexio_text_read_determinant((trexio_text_t*) file);
  if (determinant == NULL) return TREXIO_FAILURE;

  *num = determinant->determinant_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_csf_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  csf_t* csf = trexio_text_read_csf((trexio_text_t*) file);
  if (csf == NULL) return TREXIO_FAILURE;

  *num = csf->csf_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_rdm_2e_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  *num = rdm->rdm_2e_cholesky_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_rdm_2e_upup_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  *num = rdm->rdm_2e_upup_cholesky_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_rdm_2e_dndn_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  *num = rdm->rdm_2e_dndn_cholesky_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_rdm_2e_updn_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  *num = rdm->rdm_2e_updn_cholesky_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_en_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  *num = jastrow->jastrow_en_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_ee_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  *num = jastrow->jastrow_ee_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_een_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  *num = jastrow->jastrow_een_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_jastrow_ee_scaling (trexio_t* const file, double* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  *num = jastrow->jastrow_ee_scaling;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_read_qmc_num (trexio_t* const file, int64_t* const num)
{

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  qmc_t* qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  *num = qmc->qmc_num;

  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_read_determinant_coefficient(trexio_t* const file,
                                               const int64_t offset_file,
                                               const uint32_t rank,
                                               const uint64_t* dims,
                                               int64_t* const eof_read_size,
                                               double* const dset)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (dset == NULL) return TREXIO_INVALID_ARG_6;

  const char file_name[] = "/determinant_coefficient.txt";

  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly.
     Each double value 24 elements + one newline char.
   */
  uint64_t line_length = 25UL;

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[64];
  uint32_t buf_size = sizeof(buffer);
  /* Counter for number of elements beind processed */
  uint64_t count = 0UL;

  for (uint64_t i=0UL; i < dims[0]; ++i) {

    memset(buffer, 0, buf_size);
    if (fgets(buffer, buf_size-1, f) == NULL){

      fclose(f);
      *eof_read_size = count;
      return TREXIO_END;

    } else {

      rc = sscanf(buffer, "%lf", dset + i);
      if (rc <= 0) {
        fclose(f);
        return TREXIO_FAILURE;
      }
      count += 1UL;

    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_read_determinant_coefficient_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const char file_name[] = "/determinant_coefficient.txt.size";

  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64, &size_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_csf_coefficient(trexio_t* const file,
                                               const int64_t offset_file,
                                               const uint32_t rank,
                                               const uint64_t* dims,
                                               int64_t* const eof_read_size,
                                               double* const dset)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (dset == NULL) return TREXIO_INVALID_ARG_6;

  const char file_name[] = "/csf_coefficient.txt";

  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly.
     Each double value 24 elements + one newline char.
   */
  uint64_t line_length = 25UL;

  /* Offset in the file according to the provided  value of offset_file and optimal line_length */
  fseek(f, (long) offset_file * line_length, SEEK_SET);

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  char buffer[64];
  uint32_t buf_size = sizeof(buffer);
  /* Counter for number of elements beind processed */
  uint64_t count = 0UL;

  for (uint64_t i=0UL; i < dims[0]; ++i) {

    memset(buffer, 0, buf_size);
    if (fgets(buffer, buf_size-1, f) == NULL){

      fclose(f);
      *eof_read_size = count;
      return TREXIO_END;

    } else {

      rc = sscanf(buffer, "%lf", dset + i);
      if (rc <= 0) {
        fclose(f);
        return TREXIO_FAILURE;
      }
      count += 1UL;

    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_read_csf_coefficient_size(trexio_t* const file, int64_t* const size_max)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const char file_name[] = "/csf_coefficient.txt.size";

  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(file_name));

  /* Open the file in "r" (read) mode to guarantee that no truncation happens upon consecutive reads */
  FILE* f = fopen(file_full_path, "r");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Read the data from the file and check the return code of fprintf to verify that > 0 bytes have been read or reached EOF */
  int rc;
  int64_t size_item, size_accum=0L;

  /* Read the values from the file. BEWARE OF POSSIBLE MAX_INT64 OVERFLOW ! */
  while(fscanf(f, "%" SCNd64, &size_item) != EOF) {
    /* Check that summation will not overflow the int64_t value */
    if (INT64_MAX - size_accum > size_item) {
      size_accum += size_item;
    } else {
      fclose(f);
      *size_max = -1L;
      return TREXIO_INT_SIZE_OVERFLOW;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Overwrite the value at the input address and return TREXIO_SUCCESS */
  *size_max = size_accum;
  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_write_nucleus_charge (trexio_t* const file, const double* nucleus_charge,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (nucleus_charge == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->nucleus_charge != NULL) {
    FREE(nucleus->nucleus_charge);
  }

  nucleus->rank_nucleus_charge = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<nucleus->rank_nucleus_charge; ++i){
    nucleus->dims_nucleus_charge[i] = dims[i];
    dim_size *= dims[i];
  }

  nucleus->nucleus_charge = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    nucleus->nucleus_charge[i] = nucleus_charge[i];
  }

  nucleus->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_nucleus_coord (trexio_t* const file, const double* nucleus_coord,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (nucleus_coord == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->nucleus_coord != NULL) {
    FREE(nucleus->nucleus_coord);
  }

  nucleus->rank_nucleus_coord = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<nucleus->rank_nucleus_coord; ++i){
    nucleus->dims_nucleus_coord[i] = dims[i];
    dim_size *= dims[i];
  }

  nucleus->nucleus_coord = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    nucleus->nucleus_coord[i] = nucleus_coord[i];
  }

  nucleus->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_cell_a (trexio_t* const file, const double* cell_a,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (cell_a == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->cell_a != NULL) {
    FREE(cell->cell_a);
  }

  cell->rank_cell_a = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<cell->rank_cell_a; ++i){
    cell->dims_cell_a[i] = dims[i];
    dim_size *= dims[i];
  }

  cell->cell_a = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell->cell_a[i] = cell_a[i];
  }

  cell->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_cell_b (trexio_t* const file, const double* cell_b,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (cell_b == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->cell_b != NULL) {
    FREE(cell->cell_b);
  }

  cell->rank_cell_b = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<cell->rank_cell_b; ++i){
    cell->dims_cell_b[i] = dims[i];
    dim_size *= dims[i];
  }

  cell->cell_b = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell->cell_b[i] = cell_b[i];
  }

  cell->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_cell_c (trexio_t* const file, const double* cell_c,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (cell_c == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->cell_c != NULL) {
    FREE(cell->cell_c);
  }

  cell->rank_cell_c = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<cell->rank_cell_c; ++i){
    cell->dims_cell_c[i] = dims[i];
    dim_size *= dims[i];
  }

  cell->cell_c = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell->cell_c[i] = cell_c[i];
  }

  cell->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_cell_g_a (trexio_t* const file, const double* cell_g_a,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (cell_g_a == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->cell_g_a != NULL) {
    FREE(cell->cell_g_a);
  }

  cell->rank_cell_g_a = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<cell->rank_cell_g_a; ++i){
    cell->dims_cell_g_a[i] = dims[i];
    dim_size *= dims[i];
  }

  cell->cell_g_a = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell->cell_g_a[i] = cell_g_a[i];
  }

  cell->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_cell_g_b (trexio_t* const file, const double* cell_g_b,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (cell_g_b == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->cell_g_b != NULL) {
    FREE(cell->cell_g_b);
  }

  cell->rank_cell_g_b = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<cell->rank_cell_g_b; ++i){
    cell->dims_cell_g_b[i] = dims[i];
    dim_size *= dims[i];
  }

  cell->cell_g_b = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell->cell_g_b[i] = cell_g_b[i];
  }

  cell->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_cell_g_c (trexio_t* const file, const double* cell_g_c,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (cell_g_c == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  cell_t* const cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  if (cell->cell_g_c != NULL) {
    FREE(cell->cell_g_c);
  }

  cell->rank_cell_g_c = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<cell->rank_cell_g_c; ++i){
    cell->dims_cell_g_c[i] = dims[i];
    dim_size *= dims[i];
  }

  cell->cell_g_c = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    cell->cell_g_c[i] = cell_g_c[i];
  }

  cell->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_pbc_k_point (trexio_t* const file, const double* pbc_k_point,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (pbc_k_point == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  pbc_t* const pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (pbc->pbc_k_point != NULL) {
    FREE(pbc->pbc_k_point);
  }

  pbc->rank_pbc_k_point = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<pbc->rank_pbc_k_point; ++i){
    pbc->dims_pbc_k_point[i] = dims[i];
    dim_size *= dims[i];
  }

  pbc->pbc_k_point = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    pbc->pbc_k_point[i] = pbc_k_point[i];
  }

  pbc->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_pbc_k_point_weight (trexio_t* const file, const double* pbc_k_point_weight,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (pbc_k_point_weight == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  pbc_t* const pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  if (pbc->pbc_k_point_weight != NULL) {
    FREE(pbc->pbc_k_point_weight);
  }

  pbc->rank_pbc_k_point_weight = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<pbc->rank_pbc_k_point_weight; ++i){
    pbc->dims_pbc_k_point_weight[i] = dims[i];
    dim_size *= dims[i];
  }

  pbc->pbc_k_point_weight = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    pbc->pbc_k_point_weight[i] = pbc_k_point_weight[i];
  }

  pbc->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_nucleus_index (trexio_t* const file, const int64_t* basis_nucleus_index,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_nucleus_index == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_nucleus_index != NULL) {
    FREE(basis->basis_nucleus_index);
  }

  basis->rank_basis_nucleus_index = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_nucleus_index; ++i){
    basis->dims_basis_nucleus_index[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_nucleus_index = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_nucleus_index[i] = basis_nucleus_index[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_shell_ang_mom (trexio_t* const file, const int64_t* basis_shell_ang_mom,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_shell_ang_mom == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_shell_ang_mom != NULL) {
    FREE(basis->basis_shell_ang_mom);
  }

  basis->rank_basis_shell_ang_mom = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_shell_ang_mom; ++i){
    basis->dims_basis_shell_ang_mom[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_shell_ang_mom = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_shell_ang_mom[i] = basis_shell_ang_mom[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_shell_factor (trexio_t* const file, const double* basis_shell_factor,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_shell_factor == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_shell_factor != NULL) {
    FREE(basis->basis_shell_factor);
  }

  basis->rank_basis_shell_factor = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_shell_factor; ++i){
    basis->dims_basis_shell_factor[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_shell_factor = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_shell_factor[i] = basis_shell_factor[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_r_power (trexio_t* const file, const int64_t* basis_r_power,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_r_power == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_r_power != NULL) {
    FREE(basis->basis_r_power);
  }

  basis->rank_basis_r_power = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_r_power; ++i){
    basis->dims_basis_r_power[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_r_power = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_r_power[i] = basis_r_power[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_nao_grid_start (trexio_t* const file, const int64_t* basis_nao_grid_start,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_start == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_nao_grid_start != NULL) {
    FREE(basis->basis_nao_grid_start);
  }

  basis->rank_basis_nao_grid_start = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_nao_grid_start; ++i){
    basis->dims_basis_nao_grid_start[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_nao_grid_start = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_nao_grid_start[i] = basis_nao_grid_start[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_nao_grid_size (trexio_t* const file, const int64_t* basis_nao_grid_size,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_size == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_nao_grid_size != NULL) {
    FREE(basis->basis_nao_grid_size);
  }

  basis->rank_basis_nao_grid_size = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_nao_grid_size; ++i){
    basis->dims_basis_nao_grid_size[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_nao_grid_size = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_nao_grid_size[i] = basis_nao_grid_size[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_shell_index (trexio_t* const file, const int64_t* basis_shell_index,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_shell_index == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_shell_index != NULL) {
    FREE(basis->basis_shell_index);
  }

  basis->rank_basis_shell_index = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_shell_index; ++i){
    basis->dims_basis_shell_index[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_shell_index = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_shell_index[i] = basis_shell_index[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_exponent (trexio_t* const file, const double* basis_exponent,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_exponent == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_exponent != NULL) {
    FREE(basis->basis_exponent);
  }

  basis->rank_basis_exponent = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_exponent; ++i){
    basis->dims_basis_exponent[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_exponent = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_exponent[i] = basis_exponent[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_exponent_im (trexio_t* const file, const double* basis_exponent_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_exponent_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_exponent_im != NULL) {
    FREE(basis->basis_exponent_im);
  }

  basis->rank_basis_exponent_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_exponent_im; ++i){
    basis->dims_basis_exponent_im[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_exponent_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_exponent_im[i] = basis_exponent_im[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_coefficient (trexio_t* const file, const double* basis_coefficient,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_coefficient == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_coefficient != NULL) {
    FREE(basis->basis_coefficient);
  }

  basis->rank_basis_coefficient = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_coefficient; ++i){
    basis->dims_basis_coefficient[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_coefficient = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_coefficient[i] = basis_coefficient[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_coefficient_im (trexio_t* const file, const double* basis_coefficient_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_coefficient_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_coefficient_im != NULL) {
    FREE(basis->basis_coefficient_im);
  }

  basis->rank_basis_coefficient_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_coefficient_im; ++i){
    basis->dims_basis_coefficient_im[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_coefficient_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_coefficient_im[i] = basis_coefficient_im[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_oscillation_arg (trexio_t* const file, const double* basis_oscillation_arg,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_oscillation_arg == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_oscillation_arg != NULL) {
    FREE(basis->basis_oscillation_arg);
  }

  basis->rank_basis_oscillation_arg = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_oscillation_arg; ++i){
    basis->dims_basis_oscillation_arg[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_oscillation_arg = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_oscillation_arg[i] = basis_oscillation_arg[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_prim_factor (trexio_t* const file, const double* basis_prim_factor,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_prim_factor == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_prim_factor != NULL) {
    FREE(basis->basis_prim_factor);
  }

  basis->rank_basis_prim_factor = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_prim_factor; ++i){
    basis->dims_basis_prim_factor[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_prim_factor = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_prim_factor[i] = basis_prim_factor[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_nao_grid_radius (trexio_t* const file, const double* basis_nao_grid_radius,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_radius == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_nao_grid_radius != NULL) {
    FREE(basis->basis_nao_grid_radius);
  }

  basis->rank_basis_nao_grid_radius = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_nao_grid_radius; ++i){
    basis->dims_basis_nao_grid_radius[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_nao_grid_radius = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_nao_grid_radius[i] = basis_nao_grid_radius[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_nao_grid_phi (trexio_t* const file, const double* basis_nao_grid_phi,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_phi == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_nao_grid_phi != NULL) {
    FREE(basis->basis_nao_grid_phi);
  }

  basis->rank_basis_nao_grid_phi = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_nao_grid_phi; ++i){
    basis->dims_basis_nao_grid_phi[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_nao_grid_phi = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_nao_grid_phi[i] = basis_nao_grid_phi[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_nao_grid_grad (trexio_t* const file, const double* basis_nao_grid_grad,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_grad == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_nao_grid_grad != NULL) {
    FREE(basis->basis_nao_grid_grad);
  }

  basis->rank_basis_nao_grid_grad = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_nao_grid_grad; ++i){
    basis->dims_basis_nao_grid_grad[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_nao_grid_grad = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_nao_grid_grad[i] = basis_nao_grid_grad[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_nao_grid_lap (trexio_t* const file, const double* basis_nao_grid_lap,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_lap == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_nao_grid_lap != NULL) {
    FREE(basis->basis_nao_grid_lap);
  }

  basis->rank_basis_nao_grid_lap = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_nao_grid_lap; ++i){
    basis->dims_basis_nao_grid_lap[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_nao_grid_lap = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_nao_grid_lap[i] = basis_nao_grid_lap[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_interpolator_phi (trexio_t* const file, const double* basis_interpolator_phi,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_phi == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_interpolator_phi != NULL) {
    FREE(basis->basis_interpolator_phi);
  }

  basis->rank_basis_interpolator_phi = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_interpolator_phi; ++i){
    basis->dims_basis_interpolator_phi[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_interpolator_phi = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_interpolator_phi[i] = basis_interpolator_phi[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_interpolator_grad (trexio_t* const file, const double* basis_interpolator_grad,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_grad == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_interpolator_grad != NULL) {
    FREE(basis->basis_interpolator_grad);
  }

  basis->rank_basis_interpolator_grad = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_interpolator_grad; ++i){
    basis->dims_basis_interpolator_grad[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_interpolator_grad = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_interpolator_grad[i] = basis_interpolator_grad[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_interpolator_lap (trexio_t* const file, const double* basis_interpolator_lap,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_lap == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_interpolator_lap != NULL) {
    FREE(basis->basis_interpolator_lap);
  }

  basis->rank_basis_interpolator_lap = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<basis->rank_basis_interpolator_lap; ++i){
    basis->dims_basis_interpolator_lap[i] = dims[i];
    dim_size *= dims[i];
  }

  basis->basis_interpolator_lap = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    basis->basis_interpolator_lap[i] = basis_interpolator_lap[i];
  }

  basis->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ecp_max_ang_mom_plus_1 (trexio_t* const file, const int64_t* ecp_max_ang_mom_plus_1,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_max_ang_mom_plus_1 == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->ecp_max_ang_mom_plus_1 != NULL) {
    FREE(ecp->ecp_max_ang_mom_plus_1);
  }

  ecp->rank_ecp_max_ang_mom_plus_1 = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ecp->rank_ecp_max_ang_mom_plus_1; ++i){
    ecp->dims_ecp_max_ang_mom_plus_1[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_max_ang_mom_plus_1 = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp->ecp_max_ang_mom_plus_1[i] = ecp_max_ang_mom_plus_1[i];
  }

  ecp->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ecp_z_core (trexio_t* const file, const int64_t* ecp_z_core,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_z_core == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->ecp_z_core != NULL) {
    FREE(ecp->ecp_z_core);
  }

  ecp->rank_ecp_z_core = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ecp->rank_ecp_z_core; ++i){
    ecp->dims_ecp_z_core[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_z_core = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp->ecp_z_core[i] = ecp_z_core[i];
  }

  ecp->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ecp_ang_mom (trexio_t* const file, const int64_t* ecp_ang_mom,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_ang_mom == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->ecp_ang_mom != NULL) {
    FREE(ecp->ecp_ang_mom);
  }

  ecp->rank_ecp_ang_mom = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ecp->rank_ecp_ang_mom; ++i){
    ecp->dims_ecp_ang_mom[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_ang_mom = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp->ecp_ang_mom[i] = ecp_ang_mom[i];
  }

  ecp->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ecp_nucleus_index (trexio_t* const file, const int64_t* ecp_nucleus_index,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_nucleus_index == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->ecp_nucleus_index != NULL) {
    FREE(ecp->ecp_nucleus_index);
  }

  ecp->rank_ecp_nucleus_index = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ecp->rank_ecp_nucleus_index; ++i){
    ecp->dims_ecp_nucleus_index[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_nucleus_index = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp->ecp_nucleus_index[i] = ecp_nucleus_index[i];
  }

  ecp->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ecp_exponent (trexio_t* const file, const double* ecp_exponent,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_exponent == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->ecp_exponent != NULL) {
    FREE(ecp->ecp_exponent);
  }

  ecp->rank_ecp_exponent = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ecp->rank_ecp_exponent; ++i){
    ecp->dims_ecp_exponent[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_exponent = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp->ecp_exponent[i] = ecp_exponent[i];
  }

  ecp->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ecp_coefficient (trexio_t* const file, const double* ecp_coefficient,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_coefficient == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->ecp_coefficient != NULL) {
    FREE(ecp->ecp_coefficient);
  }

  ecp->rank_ecp_coefficient = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ecp->rank_ecp_coefficient; ++i){
    ecp->dims_ecp_coefficient[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_coefficient = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp->ecp_coefficient[i] = ecp_coefficient[i];
  }

  ecp->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ecp_power (trexio_t* const file, const int64_t* ecp_power,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_power == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* const ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (ecp->ecp_power != NULL) {
    FREE(ecp->ecp_power);
  }

  ecp->rank_ecp_power = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ecp->rank_ecp_power; ++i){
    ecp->dims_ecp_power[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_power = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ecp->ecp_power[i] = ecp_power[i];
  }

  ecp->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_coord (trexio_t* const file, const double* grid_coord,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (grid_coord == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_coord != NULL) {
    FREE(grid->grid_coord);
  }

  grid->rank_grid_coord = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<grid->rank_grid_coord; ++i){
    grid->dims_grid_coord[i] = dims[i];
    dim_size *= dims[i];
  }

  grid->grid_coord = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid->grid_coord[i] = grid_coord[i];
  }

  grid->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_weight (trexio_t* const file, const double* grid_weight,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (grid_weight == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_weight != NULL) {
    FREE(grid->grid_weight);
  }

  grid->rank_grid_weight = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<grid->rank_grid_weight; ++i){
    grid->dims_grid_weight[i] = dims[i];
    dim_size *= dims[i];
  }

  grid->grid_weight = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid->grid_weight[i] = grid_weight[i];
  }

  grid->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_ang_coord (trexio_t* const file, const double* grid_ang_coord,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (grid_ang_coord == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_ang_coord != NULL) {
    FREE(grid->grid_ang_coord);
  }

  grid->rank_grid_ang_coord = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<grid->rank_grid_ang_coord; ++i){
    grid->dims_grid_ang_coord[i] = dims[i];
    dim_size *= dims[i];
  }

  grid->grid_ang_coord = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid->grid_ang_coord[i] = grid_ang_coord[i];
  }

  grid->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_ang_weight (trexio_t* const file, const double* grid_ang_weight,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (grid_ang_weight == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_ang_weight != NULL) {
    FREE(grid->grid_ang_weight);
  }

  grid->rank_grid_ang_weight = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<grid->rank_grid_ang_weight; ++i){
    grid->dims_grid_ang_weight[i] = dims[i];
    dim_size *= dims[i];
  }

  grid->grid_ang_weight = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid->grid_ang_weight[i] = grid_ang_weight[i];
  }

  grid->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_rad_coord (trexio_t* const file, const double* grid_rad_coord,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (grid_rad_coord == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_rad_coord != NULL) {
    FREE(grid->grid_rad_coord);
  }

  grid->rank_grid_rad_coord = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<grid->rank_grid_rad_coord; ++i){
    grid->dims_grid_rad_coord[i] = dims[i];
    dim_size *= dims[i];
  }

  grid->grid_rad_coord = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid->grid_rad_coord[i] = grid_rad_coord[i];
  }

  grid->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_rad_weight (trexio_t* const file, const double* grid_rad_weight,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (grid_rad_weight == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_rad_weight != NULL) {
    FREE(grid->grid_rad_weight);
  }

  grid->rank_grid_rad_weight = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<grid->rank_grid_rad_weight; ++i){
    grid->dims_grid_rad_weight[i] = dims[i];
    dim_size *= dims[i];
  }

  grid->grid_rad_weight = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    grid->grid_rad_weight[i] = grid_rad_weight[i];
  }

  grid->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_shell (trexio_t* const file, const int64_t* ao_shell,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_shell == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_t* const ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  if (ao->ao_shell != NULL) {
    FREE(ao->ao_shell);
  }

  ao->rank_ao_shell = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao->rank_ao_shell; ++i){
    ao->dims_ao_shell[i] = dims[i];
    dim_size *= dims[i];
  }

  ao->ao_shell = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao->ao_shell[i] = ao_shell[i];
  }

  ao->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_normalization (trexio_t* const file, const double* ao_normalization,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_normalization == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_t* const ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  if (ao->ao_normalization != NULL) {
    FREE(ao->ao_normalization);
  }

  ao->rank_ao_normalization = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao->rank_ao_normalization; ++i){
    ao->dims_ao_normalization[i] = dims[i];
    dim_size *= dims[i];
  }

  ao->ao_normalization = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao->ao_normalization[i] = ao_normalization[i];
  }

  ao->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_overlap (trexio_t* const file, const double* ao_1e_int_overlap,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_overlap == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_overlap != NULL) {
    FREE(ao_1e_int->ao_1e_int_overlap);
  }

  ao_1e_int->rank_ao_1e_int_overlap = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_overlap; ++i){
    ao_1e_int->dims_ao_1e_int_overlap[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_overlap = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_overlap[i] = ao_1e_int_overlap[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_kinetic (trexio_t* const file, const double* ao_1e_int_kinetic,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_kinetic == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_kinetic != NULL) {
    FREE(ao_1e_int->ao_1e_int_kinetic);
  }

  ao_1e_int->rank_ao_1e_int_kinetic = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_kinetic; ++i){
    ao_1e_int->dims_ao_1e_int_kinetic[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_kinetic = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_kinetic[i] = ao_1e_int_kinetic[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_potential_n_e (trexio_t* const file, const double* ao_1e_int_potential_n_e,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_potential_n_e == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_potential_n_e != NULL) {
    FREE(ao_1e_int->ao_1e_int_potential_n_e);
  }

  ao_1e_int->rank_ao_1e_int_potential_n_e = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_potential_n_e; ++i){
    ao_1e_int->dims_ao_1e_int_potential_n_e[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_potential_n_e = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_potential_n_e[i] = ao_1e_int_potential_n_e[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_ecp (trexio_t* const file, const double* ao_1e_int_ecp,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_ecp == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_ecp != NULL) {
    FREE(ao_1e_int->ao_1e_int_ecp);
  }

  ao_1e_int->rank_ao_1e_int_ecp = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_ecp; ++i){
    ao_1e_int->dims_ao_1e_int_ecp[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_ecp = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_ecp[i] = ao_1e_int_ecp[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_core_hamiltonian (trexio_t* const file, const double* ao_1e_int_core_hamiltonian,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_core_hamiltonian == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_core_hamiltonian != NULL) {
    FREE(ao_1e_int->ao_1e_int_core_hamiltonian);
  }

  ao_1e_int->rank_ao_1e_int_core_hamiltonian = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_core_hamiltonian; ++i){
    ao_1e_int->dims_ao_1e_int_core_hamiltonian[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_core_hamiltonian = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_core_hamiltonian[i] = ao_1e_int_core_hamiltonian[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_overlap_im (trexio_t* const file, const double* ao_1e_int_overlap_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_overlap_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_overlap_im != NULL) {
    FREE(ao_1e_int->ao_1e_int_overlap_im);
  }

  ao_1e_int->rank_ao_1e_int_overlap_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_overlap_im; ++i){
    ao_1e_int->dims_ao_1e_int_overlap_im[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_overlap_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_overlap_im[i] = ao_1e_int_overlap_im[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_kinetic_im (trexio_t* const file, const double* ao_1e_int_kinetic_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_kinetic_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_kinetic_im != NULL) {
    FREE(ao_1e_int->ao_1e_int_kinetic_im);
  }

  ao_1e_int->rank_ao_1e_int_kinetic_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_kinetic_im; ++i){
    ao_1e_int->dims_ao_1e_int_kinetic_im[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_kinetic_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_kinetic_im[i] = ao_1e_int_kinetic_im[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_potential_n_e_im (trexio_t* const file, const double* ao_1e_int_potential_n_e_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_potential_n_e_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_potential_n_e_im != NULL) {
    FREE(ao_1e_int->ao_1e_int_potential_n_e_im);
  }

  ao_1e_int->rank_ao_1e_int_potential_n_e_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_potential_n_e_im; ++i){
    ao_1e_int->dims_ao_1e_int_potential_n_e_im[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_potential_n_e_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_potential_n_e_im[i] = ao_1e_int_potential_n_e_im[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_ecp_im (trexio_t* const file, const double* ao_1e_int_ecp_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_ecp_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_ecp_im != NULL) {
    FREE(ao_1e_int->ao_1e_int_ecp_im);
  }

  ao_1e_int->rank_ao_1e_int_ecp_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_ecp_im; ++i){
    ao_1e_int->dims_ao_1e_int_ecp_im[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_ecp_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_ecp_im[i] = ao_1e_int_ecp_im[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_1e_int_core_hamiltonian_im (trexio_t* const file, const double* ao_1e_int_core_hamiltonian_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_core_hamiltonian_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  ao_1e_int_t* const ao_1e_int = trexio_text_read_ao_1e_int((trexio_text_t*) file);
  if (ao_1e_int == NULL) return TREXIO_FAILURE;

  if (ao_1e_int->ao_1e_int_core_hamiltonian_im != NULL) {
    FREE(ao_1e_int->ao_1e_int_core_hamiltonian_im);
  }

  ao_1e_int->rank_ao_1e_int_core_hamiltonian_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<ao_1e_int->rank_ao_1e_int_core_hamiltonian_im; ++i){
    ao_1e_int->dims_ao_1e_int_core_hamiltonian_im[i] = dims[i];
    dim_size *= dims[i];
  }

  ao_1e_int->ao_1e_int_core_hamiltonian_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    ao_1e_int->ao_1e_int_core_hamiltonian_im[i] = ao_1e_int_core_hamiltonian_im[i];
  }

  ao_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_coefficient (trexio_t* const file, const double* mo_coefficient,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_coefficient == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_coefficient != NULL) {
    FREE(mo->mo_coefficient);
  }

  mo->rank_mo_coefficient = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo->rank_mo_coefficient; ++i){
    mo->dims_mo_coefficient[i] = dims[i];
    dim_size *= dims[i];
  }

  mo->mo_coefficient = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo->mo_coefficient[i] = mo_coefficient[i];
  }

  mo->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_coefficient_im (trexio_t* const file, const double* mo_coefficient_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_coefficient_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_coefficient_im != NULL) {
    FREE(mo->mo_coefficient_im);
  }

  mo->rank_mo_coefficient_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo->rank_mo_coefficient_im; ++i){
    mo->dims_mo_coefficient_im[i] = dims[i];
    dim_size *= dims[i];
  }

  mo->mo_coefficient_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo->mo_coefficient_im[i] = mo_coefficient_im[i];
  }

  mo->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_occupation (trexio_t* const file, const double* mo_occupation,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_occupation == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_occupation != NULL) {
    FREE(mo->mo_occupation);
  }

  mo->rank_mo_occupation = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo->rank_mo_occupation; ++i){
    mo->dims_mo_occupation[i] = dims[i];
    dim_size *= dims[i];
  }

  mo->mo_occupation = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo->mo_occupation[i] = mo_occupation[i];
  }

  mo->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_energy (trexio_t* const file, const double* mo_energy,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_energy == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_energy != NULL) {
    FREE(mo->mo_energy);
  }

  mo->rank_mo_energy = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo->rank_mo_energy; ++i){
    mo->dims_mo_energy[i] = dims[i];
    dim_size *= dims[i];
  }

  mo->mo_energy = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo->mo_energy[i] = mo_energy[i];
  }

  mo->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_spin (trexio_t* const file, const int64_t* mo_spin,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_spin == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_spin != NULL) {
    FREE(mo->mo_spin);
  }

  mo->rank_mo_spin = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo->rank_mo_spin; ++i){
    mo->dims_mo_spin[i] = dims[i];
    dim_size *= dims[i];
  }

  mo->mo_spin = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo->mo_spin[i] = mo_spin[i];
  }

  mo->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_k_point (trexio_t* const file, const int64_t* mo_k_point,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_k_point == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_k_point != NULL) {
    FREE(mo->mo_k_point);
  }

  mo->rank_mo_k_point = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo->rank_mo_k_point; ++i){
    mo->dims_mo_k_point[i] = dims[i];
    dim_size *= dims[i];
  }

  mo->mo_k_point = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo->mo_k_point[i] = mo_k_point[i];
  }

  mo->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_overlap (trexio_t* const file, const double* mo_1e_int_overlap,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_overlap == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_overlap != NULL) {
    FREE(mo_1e_int->mo_1e_int_overlap);
  }

  mo_1e_int->rank_mo_1e_int_overlap = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_overlap; ++i){
    mo_1e_int->dims_mo_1e_int_overlap[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_overlap = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_overlap[i] = mo_1e_int_overlap[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_kinetic (trexio_t* const file, const double* mo_1e_int_kinetic,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_kinetic == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_kinetic != NULL) {
    FREE(mo_1e_int->mo_1e_int_kinetic);
  }

  mo_1e_int->rank_mo_1e_int_kinetic = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_kinetic; ++i){
    mo_1e_int->dims_mo_1e_int_kinetic[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_kinetic = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_kinetic[i] = mo_1e_int_kinetic[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_potential_n_e (trexio_t* const file, const double* mo_1e_int_potential_n_e,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_potential_n_e == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_potential_n_e != NULL) {
    FREE(mo_1e_int->mo_1e_int_potential_n_e);
  }

  mo_1e_int->rank_mo_1e_int_potential_n_e = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_potential_n_e; ++i){
    mo_1e_int->dims_mo_1e_int_potential_n_e[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_potential_n_e = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_potential_n_e[i] = mo_1e_int_potential_n_e[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_ecp (trexio_t* const file, const double* mo_1e_int_ecp,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_ecp == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_ecp != NULL) {
    FREE(mo_1e_int->mo_1e_int_ecp);
  }

  mo_1e_int->rank_mo_1e_int_ecp = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_ecp; ++i){
    mo_1e_int->dims_mo_1e_int_ecp[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_ecp = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_ecp[i] = mo_1e_int_ecp[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_core_hamiltonian (trexio_t* const file, const double* mo_1e_int_core_hamiltonian,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_core_hamiltonian == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_core_hamiltonian != NULL) {
    FREE(mo_1e_int->mo_1e_int_core_hamiltonian);
  }

  mo_1e_int->rank_mo_1e_int_core_hamiltonian = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_core_hamiltonian; ++i){
    mo_1e_int->dims_mo_1e_int_core_hamiltonian[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_core_hamiltonian = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_core_hamiltonian[i] = mo_1e_int_core_hamiltonian[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_overlap_im (trexio_t* const file, const double* mo_1e_int_overlap_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_overlap_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_overlap_im != NULL) {
    FREE(mo_1e_int->mo_1e_int_overlap_im);
  }

  mo_1e_int->rank_mo_1e_int_overlap_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_overlap_im; ++i){
    mo_1e_int->dims_mo_1e_int_overlap_im[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_overlap_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_overlap_im[i] = mo_1e_int_overlap_im[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_kinetic_im (trexio_t* const file, const double* mo_1e_int_kinetic_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_kinetic_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_kinetic_im != NULL) {
    FREE(mo_1e_int->mo_1e_int_kinetic_im);
  }

  mo_1e_int->rank_mo_1e_int_kinetic_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_kinetic_im; ++i){
    mo_1e_int->dims_mo_1e_int_kinetic_im[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_kinetic_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_kinetic_im[i] = mo_1e_int_kinetic_im[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_potential_n_e_im (trexio_t* const file, const double* mo_1e_int_potential_n_e_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_potential_n_e_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_potential_n_e_im != NULL) {
    FREE(mo_1e_int->mo_1e_int_potential_n_e_im);
  }

  mo_1e_int->rank_mo_1e_int_potential_n_e_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_potential_n_e_im; ++i){
    mo_1e_int->dims_mo_1e_int_potential_n_e_im[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_potential_n_e_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_potential_n_e_im[i] = mo_1e_int_potential_n_e_im[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_ecp_im (trexio_t* const file, const double* mo_1e_int_ecp_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_ecp_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_ecp_im != NULL) {
    FREE(mo_1e_int->mo_1e_int_ecp_im);
  }

  mo_1e_int->rank_mo_1e_int_ecp_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_ecp_im; ++i){
    mo_1e_int->dims_mo_1e_int_ecp_im[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_ecp_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_ecp_im[i] = mo_1e_int_ecp_im[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_1e_int_core_hamiltonian_im (trexio_t* const file, const double* mo_1e_int_core_hamiltonian_im,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_core_hamiltonian_im == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_1e_int_t* const mo_1e_int = trexio_text_read_mo_1e_int((trexio_text_t*) file);
  if (mo_1e_int == NULL) return TREXIO_FAILURE;

  if (mo_1e_int->mo_1e_int_core_hamiltonian_im != NULL) {
    FREE(mo_1e_int->mo_1e_int_core_hamiltonian_im);
  }

  mo_1e_int->rank_mo_1e_int_core_hamiltonian_im = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<mo_1e_int->rank_mo_1e_int_core_hamiltonian_im; ++i){
    mo_1e_int->dims_mo_1e_int_core_hamiltonian_im[i] = dims[i];
    dim_size *= dims[i];
  }

  mo_1e_int->mo_1e_int_core_hamiltonian_im = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    mo_1e_int->mo_1e_int_core_hamiltonian_im[i] = mo_1e_int_core_hamiltonian_im[i];
  }

  mo_1e_int->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_rdm_1e (trexio_t* const file, const double* rdm_1e,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (rdm_1e == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rdm_1e != NULL) {
    FREE(rdm->rdm_1e);
  }

  rdm->rank_rdm_1e = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rdm->rank_rdm_1e; ++i){
    rdm->dims_rdm_1e[i] = dims[i];
    dim_size *= dims[i];
  }

  rdm->rdm_1e = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    rdm->rdm_1e[i] = rdm_1e[i];
  }

  rdm->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_rdm_1e_up (trexio_t* const file, const double* rdm_1e_up,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (rdm_1e_up == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rdm_1e_up != NULL) {
    FREE(rdm->rdm_1e_up);
  }

  rdm->rank_rdm_1e_up = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rdm->rank_rdm_1e_up; ++i){
    rdm->dims_rdm_1e_up[i] = dims[i];
    dim_size *= dims[i];
  }

  rdm->rdm_1e_up = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    rdm->rdm_1e_up[i] = rdm_1e_up[i];
  }

  rdm->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_rdm_1e_dn (trexio_t* const file, const double* rdm_1e_dn,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (rdm_1e_dn == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rdm_1e_dn != NULL) {
    FREE(rdm->rdm_1e_dn);
  }

  rdm->rank_rdm_1e_dn = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rdm->rank_rdm_1e_dn; ++i){
    rdm->dims_rdm_1e_dn[i] = dims[i];
    dim_size *= dims[i];
  }

  rdm->rdm_1e_dn = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    rdm->rdm_1e_dn[i] = rdm_1e_dn[i];
  }

  rdm->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_rdm_1e_transition (trexio_t* const file, const double* rdm_1e_transition,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (rdm_1e_transition == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  rdm_t* const rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (rdm->rdm_1e_transition != NULL) {
    FREE(rdm->rdm_1e_transition);
  }

  rdm->rank_rdm_1e_transition = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<rdm->rank_rdm_1e_transition; ++i){
    rdm->dims_rdm_1e_transition[i] = dims[i];
    dim_size *= dims[i];
  }

  rdm->rdm_1e_transition = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    rdm->rdm_1e_transition[i] = rdm_1e_transition[i];
  }

  rdm->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_en (trexio_t* const file, const double* jastrow_en,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (jastrow_en == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_en != NULL) {
    FREE(jastrow->jastrow_en);
  }

  jastrow->rank_jastrow_en = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<jastrow->rank_jastrow_en; ++i){
    jastrow->dims_jastrow_en[i] = dims[i];
    dim_size *= dims[i];
  }

  jastrow->jastrow_en = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow->jastrow_en[i] = jastrow_en[i];
  }

  jastrow->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_ee (trexio_t* const file, const double* jastrow_ee,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (jastrow_ee == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_ee != NULL) {
    FREE(jastrow->jastrow_ee);
  }

  jastrow->rank_jastrow_ee = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<jastrow->rank_jastrow_ee; ++i){
    jastrow->dims_jastrow_ee[i] = dims[i];
    dim_size *= dims[i];
  }

  jastrow->jastrow_ee = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow->jastrow_ee[i] = jastrow_ee[i];
  }

  jastrow->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_een (trexio_t* const file, const double* jastrow_een,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (jastrow_een == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_een != NULL) {
    FREE(jastrow->jastrow_een);
  }

  jastrow->rank_jastrow_een = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<jastrow->rank_jastrow_een; ++i){
    jastrow->dims_jastrow_een[i] = dims[i];
    dim_size *= dims[i];
  }

  jastrow->jastrow_een = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow->jastrow_een[i] = jastrow_een[i];
  }

  jastrow->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_en_nucleus (trexio_t* const file, const int64_t* jastrow_en_nucleus,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (jastrow_en_nucleus == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_en_nucleus != NULL) {
    FREE(jastrow->jastrow_en_nucleus);
  }

  jastrow->rank_jastrow_en_nucleus = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<jastrow->rank_jastrow_en_nucleus; ++i){
    jastrow->dims_jastrow_en_nucleus[i] = dims[i];
    dim_size *= dims[i];
  }

  jastrow->jastrow_en_nucleus = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow->jastrow_en_nucleus[i] = jastrow_en_nucleus[i];
  }

  jastrow->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_een_nucleus (trexio_t* const file, const int64_t* jastrow_een_nucleus,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (jastrow_een_nucleus == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_een_nucleus != NULL) {
    FREE(jastrow->jastrow_een_nucleus);
  }

  jastrow->rank_jastrow_een_nucleus = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<jastrow->rank_jastrow_een_nucleus; ++i){
    jastrow->dims_jastrow_een_nucleus[i] = dims[i];
    dim_size *= dims[i];
  }

  jastrow->jastrow_een_nucleus = CALLOC(dim_size, int64_t);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow->jastrow_een_nucleus[i] = jastrow_een_nucleus[i];
  }

  jastrow->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_en_scaling (trexio_t* const file, const double* jastrow_en_scaling,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (jastrow_en_scaling == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_en_scaling != NULL) {
    FREE(jastrow->jastrow_en_scaling);
  }

  jastrow->rank_jastrow_en_scaling = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<jastrow->rank_jastrow_en_scaling; ++i){
    jastrow->dims_jastrow_en_scaling[i] = dims[i];
    dim_size *= dims[i];
  }

  jastrow->jastrow_en_scaling = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    jastrow->jastrow_en_scaling[i] = jastrow_en_scaling[i];
  }

  jastrow->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_qmc_point (trexio_t* const file, const double* qmc_point,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (qmc_point == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (qmc->qmc_point != NULL) {
    FREE(qmc->qmc_point);
  }

  qmc->rank_qmc_point = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<qmc->rank_qmc_point; ++i){
    qmc->dims_qmc_point[i] = dims[i];
    dim_size *= dims[i];
  }

  qmc->qmc_point = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    qmc->qmc_point[i] = qmc_point[i];
  }

  qmc->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_qmc_psi (trexio_t* const file, const double* qmc_psi,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (qmc_psi == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (qmc->qmc_psi != NULL) {
    FREE(qmc->qmc_psi);
  }

  qmc->rank_qmc_psi = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<qmc->rank_qmc_psi; ++i){
    qmc->dims_qmc_psi[i] = dims[i];
    dim_size *= dims[i];
  }

  qmc->qmc_psi = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    qmc->qmc_psi[i] = qmc_psi[i];
  }

  qmc->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_qmc_e_loc (trexio_t* const file, const double* qmc_e_loc,
                                const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (qmc_e_loc == NULL)  return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  if (file->mode == 'r') return TREXIO_READONLY;

  qmc_t* const qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  if (qmc->qmc_e_loc != NULL) {
    FREE(qmc->qmc_e_loc);
  }

  qmc->rank_qmc_e_loc = rank;

  uint64_t dim_size = 1;
  for (uint32_t i=0; i<qmc->rank_qmc_e_loc; ++i){
    qmc->dims_qmc_e_loc[i] = dims[i];
    dim_size *= dims[i];
  }

  qmc->qmc_e_loc = CALLOC(dim_size, double);

  for (uint64_t i=0 ; i<dim_size ; ++i) {
    qmc->qmc_e_loc[i] = qmc_e_loc[i];
  }

  qmc->to_flush = 1;
  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_metadata_code (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (dset == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->metadata_code != NULL) {
    if (metadata->rank_metadata_code != 0) FREE(metadata->metadata_code[0]);
    FREE(metadata->metadata_code);
  }

  metadata->rank_metadata_code = rank;

  for (uint32_t i=0; i<metadata->rank_metadata_code; ++i){
    metadata->dims_metadata_code[i] = dims[i];
  }

  metadata->metadata_code = CALLOC(dims[0], char*);
  if (metadata->metadata_code == NULL) return TREXIO_ALLOCATION_FAILED;

  char* tmp_str = CALLOC(dims[0]*32 + 1, char);
  if (tmp_str == NULL) return TREXIO_ALLOCATION_FAILED;

  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    size_t tmp_len = strlen(dset[i])+1;
    metadata->metadata_code[i] = tmp_str;
    strncpy(tmp_str, dset[i], tmp_len);
    tmp_str[tmp_len-1] = '\0';
    tmp_str += tmp_len + 1;
  }

  metadata->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_metadata_author (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (dset == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->metadata_author != NULL) {
    if (metadata->rank_metadata_author != 0) FREE(metadata->metadata_author[0]);
    FREE(metadata->metadata_author);
  }

  metadata->rank_metadata_author = rank;

  for (uint32_t i=0; i<metadata->rank_metadata_author; ++i){
    metadata->dims_metadata_author[i] = dims[i];
  }

  metadata->metadata_author = CALLOC(dims[0], char*);
  if (metadata->metadata_author == NULL) return TREXIO_ALLOCATION_FAILED;

  char* tmp_str = CALLOC(dims[0]*32 + 1, char);
  if (tmp_str == NULL) return TREXIO_ALLOCATION_FAILED;

  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    size_t tmp_len = strlen(dset[i])+1;
    metadata->metadata_author[i] = tmp_str;
    strncpy(tmp_str, dset[i], tmp_len);
    tmp_str[tmp_len-1] = '\0';
    tmp_str += tmp_len + 1;
  }

  metadata->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_nucleus_label (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (dset == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->nucleus_label != NULL) {
    if (nucleus->rank_nucleus_label != 0) FREE(nucleus->nucleus_label[0]);
    FREE(nucleus->nucleus_label);
  }

  nucleus->rank_nucleus_label = rank;

  for (uint32_t i=0; i<nucleus->rank_nucleus_label; ++i){
    nucleus->dims_nucleus_label[i] = dims[i];
  }

  nucleus->nucleus_label = CALLOC(dims[0], char*);
  if (nucleus->nucleus_label == NULL) return TREXIO_ALLOCATION_FAILED;

  char* tmp_str = CALLOC(dims[0]*32 + 1, char);
  if (tmp_str == NULL) return TREXIO_ALLOCATION_FAILED;

  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    size_t tmp_len = strlen(dset[i])+1;
    nucleus->nucleus_label[i] = tmp_str;
    strncpy(tmp_str, dset[i], tmp_len);
    tmp_str[tmp_len-1] = '\0';
    tmp_str += tmp_len + 1;
  }

  nucleus->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_state_label (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (dset == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->state_label != NULL) {
    if (state->rank_state_label != 0) FREE(state->state_label[0]);
    FREE(state->state_label);
  }

  state->rank_state_label = rank;

  for (uint32_t i=0; i<state->rank_state_label; ++i){
    state->dims_state_label[i] = dims[i];
  }

  state->state_label = CALLOC(dims[0], char*);
  if (state->state_label == NULL) return TREXIO_ALLOCATION_FAILED;

  char* tmp_str = CALLOC(dims[0]*32 + 1, char);
  if (tmp_str == NULL) return TREXIO_ALLOCATION_FAILED;

  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    size_t tmp_len = strlen(dset[i])+1;
    state->state_label[i] = tmp_str;
    strncpy(tmp_str, dset[i], tmp_len);
    tmp_str[tmp_len-1] = '\0';
    tmp_str += tmp_len + 1;
  }

  state->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_state_file_name (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (dset == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->state_file_name != NULL) {
    if (state->rank_state_file_name != 0) FREE(state->state_file_name[0]);
    FREE(state->state_file_name);
  }

  state->rank_state_file_name = rank;

  for (uint32_t i=0; i<state->rank_state_file_name; ++i){
    state->dims_state_file_name[i] = dims[i];
  }

  state->state_file_name = CALLOC(dims[0], char*);
  if (state->state_file_name == NULL) return TREXIO_ALLOCATION_FAILED;

  char* tmp_str = CALLOC(dims[0]*32 + 1, char);
  if (tmp_str == NULL) return TREXIO_ALLOCATION_FAILED;

  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    size_t tmp_len = strlen(dset[i])+1;
    state->state_file_name[i] = tmp_str;
    strncpy(tmp_str, dset[i], tmp_len);
    tmp_str[tmp_len-1] = '\0';
    tmp_str += tmp_len + 1;
  }

  state->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_class (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (dset == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_class != NULL) {
    if (mo->rank_mo_class != 0) FREE(mo->mo_class[0]);
    FREE(mo->mo_class);
  }

  mo->rank_mo_class = rank;

  for (uint32_t i=0; i<mo->rank_mo_class; ++i){
    mo->dims_mo_class[i] = dims[i];
  }

  mo->mo_class = CALLOC(dims[0], char*);
  if (mo->mo_class == NULL) return TREXIO_ALLOCATION_FAILED;

  char* tmp_str = CALLOC(dims[0]*32 + 1, char);
  if (tmp_str == NULL) return TREXIO_ALLOCATION_FAILED;

  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    size_t tmp_len = strlen(dset[i])+1;
    mo->mo_class[i] = tmp_str;
    strncpy(tmp_str, dset[i], tmp_len);
    tmp_str[tmp_len-1] = '\0';
    tmp_str += tmp_len + 1;
  }

  mo->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_symmetry (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims)
{

  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (dset == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_symmetry != NULL) {
    if (mo->rank_mo_symmetry != 0) FREE(mo->mo_symmetry[0]);
    FREE(mo->mo_symmetry);
  }

  mo->rank_mo_symmetry = rank;

  for (uint32_t i=0; i<mo->rank_mo_symmetry; ++i){
    mo->dims_mo_symmetry[i] = dims[i];
  }

  mo->mo_symmetry = CALLOC(dims[0], char*);
  if (mo->mo_symmetry == NULL) return TREXIO_ALLOCATION_FAILED;

  char* tmp_str = CALLOC(dims[0]*32 + 1, char);
  if (tmp_str == NULL) return TREXIO_ALLOCATION_FAILED;

  for (uint64_t i=0 ; i<dims[0] ; ++i) {
    size_t tmp_len = strlen(dset[i])+1;
    mo->mo_symmetry[i] = tmp_str;
    strncpy(tmp_str, dset[i], tmp_len);
    tmp_str[tmp_len-1] = '\0';
    tmp_str += tmp_len + 1;
  }

  mo->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_write_ao_2e_int_eri(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The ao_2e_int_eri.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char ao_2e_int_eri_file_name[] = "/ao_2e_int_eri.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char ao_2e_int_file_name[] = "/ao_2e_int.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_ao_2e_int_eri_lr(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The ao_2e_int_eri_lr.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char ao_2e_int_eri_lr_file_name[] = "/ao_2e_int_eri_lr.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_lr_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_lr_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char ao_2e_int_file_name[] = "/ao_2e_int.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_ao_2e_int_eri_cholesky(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The ao_2e_int_eri_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char ao_2e_int_eri_cholesky_file_name[] = "/ao_2e_int_eri_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_cholesky_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 58; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 3*i), *(index_sparse + 3*i + 1), *(index_sparse + 3*i + 2),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char ao_2e_int_file_name[] = "/ao_2e_int.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_ao_2e_int_eri_lr_cholesky(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The ao_2e_int_eri_lr_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char ao_2e_int_eri_lr_cholesky_file_name[] = "/ao_2e_int_eri_lr_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_eri_lr_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_eri_lr_cholesky_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 58; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 3*i), *(index_sparse + 3*i + 1), *(index_sparse + 3*i + 2),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char ao_2e_int_file_name[] = "/ao_2e_int.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, ao_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(ao_2e_int_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_mo_2e_int_eri(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The mo_2e_int_eri.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char mo_2e_int_eri_file_name[] = "/mo_2e_int_eri.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char mo_2e_int_file_name[] = "/mo_2e_int.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_mo_2e_int_eri_lr(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The mo_2e_int_eri_lr.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char mo_2e_int_eri_lr_file_name[] = "/mo_2e_int_eri_lr.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_lr_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_lr_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char mo_2e_int_file_name[] = "/mo_2e_int.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_mo_2e_int_eri_cholesky(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The mo_2e_int_eri_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char mo_2e_int_eri_cholesky_file_name[] = "/mo_2e_int_eri_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_cholesky_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 58; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 3*i), *(index_sparse + 3*i + 1), *(index_sparse + 3*i + 2),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char mo_2e_int_file_name[] = "/mo_2e_int.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_mo_2e_int_eri_lr_cholesky(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The mo_2e_int_eri_lr_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char mo_2e_int_eri_lr_cholesky_file_name[] = "/mo_2e_int_eri_lr_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_eri_lr_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_eri_lr_cholesky_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 58; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 3*i), *(index_sparse + 3*i + 1), *(index_sparse + 3*i + 2),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char mo_2e_int_file_name[] = "/mo_2e_int.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, mo_2e_int_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(mo_2e_int_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_csf_det_coefficient(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The csf_det_coefficient.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char csf_det_coefficient_file_name[] = "/csf_det_coefficient.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, csf_det_coefficient_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(csf_det_coefficient_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 33; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 37; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 47; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 2*i), *(index_sparse + 2*i + 1),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char csf_file_name[] = "/csf.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, csf_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(csf_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_amplitude_single(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The amplitude_single.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char amplitude_single_file_name[] = "/amplitude_single.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_single_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_single_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 33; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 37; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 47; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 2*i), *(index_sparse + 2*i + 1),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char amplitude_file_name[] = "/amplitude.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_amplitude_single_exp(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The amplitude_single_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char amplitude_single_exp_file_name[] = "/amplitude_single_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_single_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_single_exp_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 33; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 37; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 47; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 2*i), *(index_sparse + 2*i + 1),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char amplitude_file_name[] = "/amplitude.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_amplitude_double(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The amplitude_double.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char amplitude_double_file_name[] = "/amplitude_double.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_double_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_double_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char amplitude_file_name[] = "/amplitude.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_amplitude_double_exp(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The amplitude_double_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char amplitude_double_exp_file_name[] = "/amplitude_double_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_double_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_double_exp_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char amplitude_file_name[] = "/amplitude.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_amplitude_triple(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The amplitude_triple.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char amplitude_triple_file_name[] = "/amplitude_triple.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_triple_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_triple_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 49; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 61; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 91; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 6*i), *(index_sparse + 6*i + 1), *(index_sparse + 6*i + 2), *(index_sparse + 6*i + 3), *(index_sparse + 6*i + 4), *(index_sparse + 6*i + 5),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char amplitude_file_name[] = "/amplitude.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_amplitude_triple_exp(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The amplitude_triple_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char amplitude_triple_exp_file_name[] = "/amplitude_triple_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_triple_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_triple_exp_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 49; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 61; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 91; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 6*i), *(index_sparse + 6*i + 1), *(index_sparse + 6*i + 2), *(index_sparse + 6*i + 3), *(index_sparse + 6*i + 4), *(index_sparse + 6*i + 5),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char amplitude_file_name[] = "/amplitude.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_amplitude_quadruple(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The amplitude_quadruple.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char amplitude_quadruple_file_name[] = "/amplitude_quadruple.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_quadruple_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_quadruple_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 57; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 73; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 113; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 8*i), *(index_sparse + 8*i + 1), *(index_sparse + 8*i + 2), *(index_sparse + 8*i + 3), *(index_sparse + 8*i + 4), *(index_sparse + 8*i + 5), *(index_sparse + 8*i + 6), *(index_sparse + 8*i + 7),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char amplitude_file_name[] = "/amplitude.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_amplitude_quadruple_exp(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The amplitude_quadruple_exp.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char amplitude_quadruple_exp_file_name[] = "/amplitude_quadruple_exp.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_quadruple_exp_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_quadruple_exp_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 57; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 73; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 113; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 8*i), *(index_sparse + 8*i + 1), *(index_sparse + 8*i + 2), *(index_sparse + 8*i + 3), *(index_sparse + 8*i + 4), *(index_sparse + 8*i + 5), *(index_sparse + 8*i + 6), *(index_sparse + 8*i + 7),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char amplitude_file_name[] = "/amplitude.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, amplitude_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(amplitude_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_file_name[] = "/rdm_2e.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e_upup(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e_upup.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_upup_file_name[] = "/rdm_2e_upup.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_upup_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_upup_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e_dndn(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e_dndn.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_dndn_file_name[] = "/rdm_2e_dndn.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_dndn_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_dndn_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e_updn(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e_updn.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_updn_file_name[] = "/rdm_2e_updn.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_updn_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_updn_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 41; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 49; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 69; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 4*i), *(index_sparse + 4*i + 1), *(index_sparse + 4*i + 2), *(index_sparse + 4*i + 3),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e_transition(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e_transition.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_transition_file_name[] = "/rdm_2e_transition.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_transition_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_transition_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 49; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 61; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 91; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 6*i), *(index_sparse + 6*i + 1), *(index_sparse + 6*i + 2), *(index_sparse + 6*i + 3), *(index_sparse + 6*i + 4), *(index_sparse + 6*i + 5),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e_cholesky(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_cholesky_file_name[] = "/rdm_2e_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_cholesky_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 58; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 3*i), *(index_sparse + 3*i + 1), *(index_sparse + 3*i + 2),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e_upup_cholesky(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e_upup_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_upup_cholesky_file_name[] = "/rdm_2e_upup_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_upup_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_upup_cholesky_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 58; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 3*i), *(index_sparse + 3*i + 1), *(index_sparse + 3*i + 2),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e_dndn_cholesky(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e_dndn_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_dndn_cholesky_file_name[] = "/rdm_2e_dndn_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_dndn_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_dndn_cholesky_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 58; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 3*i), *(index_sparse + 3*i + 1), *(index_sparse + 3*i + 2),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_rdm_2e_updn_cholesky(trexio_t* const file,
                                                const int64_t offset_file,
                                                const int64_t size,
                                                const int64_t size_max,
                                                const int64_t size_start,
                                                const int32_t* index_sparse,
                                                const double* value_sparse)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  /* Build the name of the file with sparse data*/
  /* The rdm_2e_updn_cholesky.txt is limited to 256 symbols for the moment. What are the chances that it will exceed? */
  const char rdm_2e_updn_cholesky_file_name[] = "/rdm_2e_updn_cholesky.txt";
  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];

  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_2e_updn_cholesky_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_2e_updn_cholesky_file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Specify the line length in order to offset properly. For example, for 4-index quantities
     the line_length is 69 because 10 per index + 4 spaces + 24 for floating point value + 1 for the new line char.
     CURRENTLY NO OFFSET IS USED WHEN WRITING !
    */
  (void) offset_file; // Avoid unused variable error
  
  int64_t line_length = 0L;
  char format_str[256];

  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    line_length = 37; // 41 for 4 indices
    strncpy(format_str, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 " %24.16e" , 256);
    format_str[255] = '\0';
  } else if (size_max < UINT16_MAX) {
    line_length = 43; // 49 for 4 indices
    strncpy(format_str, "%5" PRIu16 " %5" PRIu16 " %5" PRIu16 " %24.16e" , 256);
    format_str[255] = '\0';
  } else {
    line_length = 58; //69 for 4 indices
    strncpy(format_str, "%10" PRId32 " %10" PRId32 " %10" PRId32 " %24.16e" , 256);
    format_str[255] = '\0';
  }
  strncat(format_str, "\n", 2);

  /* Get the starting position of the IO stream to be written in the .size file.
     This is error-prone due to the fact that for large files (>2 GB) in 32-bit systems ftell will fail.
     One can use ftello function which is adapted for large files.
     For now, we can use front-end-provided size_start, which has been checked for INT64_MAX overflow.
   */
  int64_t io_start_pos = size_start * line_length;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < (uint64_t) size; ++i) {
    rc = fprintf(f, format_str,
       *(index_sparse + 3*i), *(index_sparse + 3*i + 1), *(index_sparse + 3*i + 2),
       *(value_sparse + i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }
  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", 6);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRId64 " %" PRId64 "\n", size, io_start_pos);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  const char rdm_file_name[] = "/rdm.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, rdm_file_name,
           TREXIO_MAX_FILENAME_LENGTH-strlen(rdm_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_text_write_metadata_package_version (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->metadata_package_version != NULL) FREE(metadata->metadata_package_version);

  size_t tmp_len = strlen(str);

  metadata->metadata_package_version = CALLOC(tmp_len + 1, char);
  if (metadata->metadata_package_version == NULL) return TREXIO_ALLOCATION_FAILED;

  metadata->len_metadata_package_version = tmp_len + 1;

  strncpy(metadata->metadata_package_version, str, tmp_len + 1);
  metadata->metadata_package_version[tmp_len] = '\0';

  metadata->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_metadata_description (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  metadata_t* const metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  if (metadata->metadata_description != NULL) FREE(metadata->metadata_description);

  size_t tmp_len = strlen(str);

  metadata->metadata_description = CALLOC(tmp_len + 1, char);
  if (metadata->metadata_description == NULL) return TREXIO_ALLOCATION_FAILED;

  metadata->len_metadata_description = tmp_len + 1;

  strncpy(metadata->metadata_description, str, tmp_len + 1);
  metadata->metadata_description[tmp_len] = '\0';

  metadata->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_nucleus_point_group (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* const nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (nucleus->nucleus_point_group != NULL) FREE(nucleus->nucleus_point_group);

  size_t tmp_len = strlen(str);

  nucleus->nucleus_point_group = CALLOC(tmp_len + 1, char);
  if (nucleus->nucleus_point_group == NULL) return TREXIO_ALLOCATION_FAILED;

  nucleus->len_nucleus_point_group = tmp_len + 1;

  strncpy(nucleus->nucleus_point_group, str, tmp_len + 1);
  nucleus->nucleus_point_group[tmp_len] = '\0';

  nucleus->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_state_current_label (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  state_t* const state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  if (state->state_current_label != NULL) FREE(state->state_current_label);

  size_t tmp_len = strlen(str);

  state->state_current_label = CALLOC(tmp_len + 1, char);
  if (state->state_current_label == NULL) return TREXIO_ALLOCATION_FAILED;

  state->len_state_current_label = tmp_len + 1;

  strncpy(state->state_current_label, str, tmp_len + 1);
  state->state_current_label[tmp_len] = '\0';

  state->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_type (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_type != NULL) FREE(basis->basis_type);

  size_t tmp_len = strlen(str);

  basis->basis_type = CALLOC(tmp_len + 1, char);
  if (basis->basis_type == NULL) return TREXIO_ALLOCATION_FAILED;

  basis->len_basis_type = tmp_len + 1;

  strncpy(basis->basis_type, str, tmp_len + 1);
  basis->basis_type[tmp_len] = '\0';

  basis->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_oscillation_kind (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_oscillation_kind != NULL) FREE(basis->basis_oscillation_kind);

  size_t tmp_len = strlen(str);

  basis->basis_oscillation_kind = CALLOC(tmp_len + 1, char);
  if (basis->basis_oscillation_kind == NULL) return TREXIO_ALLOCATION_FAILED;

  basis->len_basis_oscillation_kind = tmp_len + 1;

  strncpy(basis->basis_oscillation_kind, str, tmp_len + 1);
  basis->basis_oscillation_kind[tmp_len] = '\0';

  basis->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_interpolator_kind (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* const basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  if (basis->basis_interpolator_kind != NULL) FREE(basis->basis_interpolator_kind);

  size_t tmp_len = strlen(str);

  basis->basis_interpolator_kind = CALLOC(tmp_len + 1, char);
  if (basis->basis_interpolator_kind == NULL) return TREXIO_ALLOCATION_FAILED;

  basis->len_basis_interpolator_kind = tmp_len + 1;

  strncpy(basis->basis_interpolator_kind, str, tmp_len + 1);
  basis->basis_interpolator_kind[tmp_len] = '\0';

  basis->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_description (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* const grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  if (grid->grid_description != NULL) FREE(grid->grid_description);

  size_t tmp_len = strlen(str);

  grid->grid_description = CALLOC(tmp_len + 1, char);
  if (grid->grid_description == NULL) return TREXIO_ALLOCATION_FAILED;

  grid->len_grid_description = tmp_len + 1;

  strncpy(grid->grid_description, str, tmp_len + 1);
  grid->grid_description[tmp_len] = '\0';

  grid->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_type (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* const mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  if (mo->mo_type != NULL) FREE(mo->mo_type);

  size_t tmp_len = strlen(str);

  mo->mo_type = CALLOC(tmp_len + 1, char);
  if (mo->mo_type == NULL) return TREXIO_ALLOCATION_FAILED;

  mo->len_mo_type = tmp_len + 1;

  strncpy(mo->mo_type, str, tmp_len + 1);
  mo->mo_type[tmp_len] = '\0';

  mo->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_type (trexio_t* const file, const char *str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* const jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  if (jastrow->jastrow_type != NULL) FREE(jastrow->jastrow_type);

  size_t tmp_len = strlen(str);

  jastrow->jastrow_type = CALLOC(tmp_len + 1, char);
  if (jastrow->jastrow_type == NULL) return TREXIO_ALLOCATION_FAILED;

  jastrow->len_jastrow_type = tmp_len + 1;

  strncpy(jastrow->jastrow_type, str, tmp_len + 1);
  jastrow->jastrow_type[tmp_len] = '\0';

  jastrow->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_metadata_code_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  metadata->metadata_code_num = num;
  metadata->metadata_code_num_isSet = true;
  metadata->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_metadata_author_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  metadata->metadata_author_num = num;
  metadata->metadata_author_num_isSet = true;
  metadata->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_metadata_unsafe (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  metadata_t* metadata = trexio_text_read_metadata((trexio_text_t*) file);
  if (metadata == NULL) return TREXIO_FAILURE;

  metadata->metadata_unsafe = num;
  metadata->metadata_unsafe_isSet = true;
  metadata->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_nucleus_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  nucleus->nucleus_num = num;
  nucleus->nucleus_num_isSet = true;
  nucleus->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_nucleus_repulsion (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  nucleus->nucleus_repulsion = num;
  nucleus->nucleus_repulsion_isSet = true;
  nucleus->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_cell_two_pi (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  cell_t* cell = trexio_text_read_cell((trexio_text_t*) file);
  if (cell == NULL) return TREXIO_FAILURE;

  cell->cell_two_pi = num;
  cell->cell_two_pi_isSet = true;
  cell->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_pbc_periodic (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  pbc->pbc_periodic = num;
  pbc->pbc_periodic_isSet = true;
  pbc->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_pbc_k_point_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  pbc->pbc_k_point_num = num;
  pbc->pbc_k_point_num_isSet = true;
  pbc->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_pbc_madelung (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  pbc_t* pbc = trexio_text_read_pbc((trexio_text_t*) file);
  if (pbc == NULL) return TREXIO_FAILURE;

  pbc->pbc_madelung = num;
  pbc->pbc_madelung_isSet = true;
  pbc->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_electron_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  electron->electron_num = num;
  electron->electron_num_isSet = true;
  electron->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_electron_up_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  electron->electron_up_num = num;
  electron->electron_up_num_isSet = true;
  electron->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_electron_dn_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  electron_t* electron = trexio_text_read_electron((trexio_text_t*) file);
  if (electron == NULL) return TREXIO_FAILURE;

  electron->electron_dn_num = num;
  electron->electron_dn_num_isSet = true;
  electron->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_state_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  state->state_num = num;
  state->state_num_isSet = true;
  state->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_state_id (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  state->state_id = num;
  state->state_id_isSet = true;
  state->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_state_energy (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  state_t* state = trexio_text_read_state((trexio_text_t*) file);
  if (state == NULL) return TREXIO_FAILURE;

  state->state_energy = num;
  state->state_energy_isSet = true;
  state->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_prim_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  basis->basis_prim_num = num;
  basis->basis_prim_num_isSet = true;
  basis->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_shell_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  basis->basis_shell_num = num;
  basis->basis_shell_num_isSet = true;
  basis->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_nao_grid_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  basis->basis_nao_grid_num = num;
  basis->basis_nao_grid_num_isSet = true;
  basis->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_interp_coeff_cnt (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  basis->basis_interp_coeff_cnt = num;
  basis->basis_interp_coeff_cnt_isSet = true;
  basis->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_basis_e_cut (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  basis_t* basis = trexio_text_read_basis((trexio_text_t*) file);
  if (basis == NULL) return TREXIO_FAILURE;

  basis->basis_e_cut = num;
  basis->basis_e_cut_isSet = true;
  basis->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ecp_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  ecp->ecp_num = num;
  ecp->ecp_num_isSet = true;
  ecp->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_rad_precision (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  grid->grid_rad_precision = num;
  grid->grid_rad_precision_isSet = true;
  grid->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  grid->grid_num = num;
  grid->grid_num_isSet = true;
  grid->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_max_ang_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  grid->grid_max_ang_num = num;
  grid->grid_max_ang_num_isSet = true;
  grid->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_min_ang_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  grid->grid_min_ang_num = num;
  grid->grid_min_ang_num_isSet = true;
  grid->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_ang_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  grid->grid_ang_num = num;
  grid->grid_ang_num_isSet = true;
  grid->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_grid_rad_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  grid_t* grid = trexio_text_read_grid((trexio_text_t*) file);
  if (grid == NULL) return TREXIO_FAILURE;

  grid->grid_rad_num = num;
  grid->grid_rad_num_isSet = true;
  grid->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_cartesian (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  ao_t* ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  ao->ao_cartesian = num;
  ao->ao_cartesian_isSet = true;
  ao->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  ao_t* ao = trexio_text_read_ao((trexio_text_t*) file);
  if (ao == NULL) return TREXIO_FAILURE;

  ao->ao_num = num;
  ao->ao_num_isSet = true;
  ao->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_2e_int_eri_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  ao_2e_int_t* ao_2e_int = trexio_text_read_ao_2e_int((trexio_text_t*) file);
  if (ao_2e_int == NULL) return TREXIO_FAILURE;

  ao_2e_int->ao_2e_int_eri_cholesky_num = num;
  ao_2e_int->ao_2e_int_eri_cholesky_num_isSet = true;
  ao_2e_int->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  ao_2e_int_t* ao_2e_int = trexio_text_read_ao_2e_int((trexio_text_t*) file);
  if (ao_2e_int == NULL) return TREXIO_FAILURE;

  ao_2e_int->ao_2e_int_eri_lr_cholesky_num = num;
  ao_2e_int->ao_2e_int_eri_lr_cholesky_num_isSet = true;
  ao_2e_int->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  mo_t* mo = trexio_text_read_mo((trexio_text_t*) file);
  if (mo == NULL) return TREXIO_FAILURE;

  mo->mo_num = num;
  mo->mo_num_isSet = true;
  mo->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_2e_int_eri_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  mo_2e_int_t* mo_2e_int = trexio_text_read_mo_2e_int((trexio_text_t*) file);
  if (mo_2e_int == NULL) return TREXIO_FAILURE;

  mo_2e_int->mo_2e_int_eri_cholesky_num = num;
  mo_2e_int->mo_2e_int_eri_cholesky_num_isSet = true;
  mo_2e_int->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  mo_2e_int_t* mo_2e_int = trexio_text_read_mo_2e_int((trexio_text_t*) file);
  if (mo_2e_int == NULL) return TREXIO_FAILURE;

  mo_2e_int->mo_2e_int_eri_lr_cholesky_num = num;
  mo_2e_int->mo_2e_int_eri_lr_cholesky_num_isSet = true;
  mo_2e_int->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_determinant_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  determinant_t* determinant = trexio_text_read_determinant((trexio_text_t*) file);
  if (determinant == NULL) return TREXIO_FAILURE;

  determinant->determinant_num = num;
  determinant->determinant_num_isSet = true;
  determinant->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_csf_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  csf_t* csf = trexio_text_read_csf((trexio_text_t*) file);
  if (csf == NULL) return TREXIO_FAILURE;

  csf->csf_num = num;
  csf->csf_num_isSet = true;
  csf->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_rdm_2e_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  rdm->rdm_2e_cholesky_num = num;
  rdm->rdm_2e_cholesky_num_isSet = true;
  rdm->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_rdm_2e_upup_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  rdm->rdm_2e_upup_cholesky_num = num;
  rdm->rdm_2e_upup_cholesky_num_isSet = true;
  rdm->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_rdm_2e_dndn_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  rdm->rdm_2e_dndn_cholesky_num = num;
  rdm->rdm_2e_dndn_cholesky_num_isSet = true;
  rdm->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_rdm_2e_updn_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  rdm->rdm_2e_updn_cholesky_num = num;
  rdm->rdm_2e_updn_cholesky_num_isSet = true;
  rdm->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_en_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  jastrow->jastrow_en_num = num;
  jastrow->jastrow_en_num_isSet = true;
  jastrow->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_ee_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  jastrow->jastrow_ee_num = num;
  jastrow->jastrow_ee_num_isSet = true;
  jastrow->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_een_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  jastrow->jastrow_een_num = num;
  jastrow->jastrow_een_num_isSet = true;
  jastrow->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_jastrow_ee_scaling (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  jastrow_t* jastrow = trexio_text_read_jastrow((trexio_text_t*) file);
  if (jastrow == NULL) return TREXIO_FAILURE;

  jastrow->jastrow_ee_scaling = num;
  jastrow->jastrow_ee_scaling_isSet = true;
  jastrow->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_text_write_qmc_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (file->mode == 'r') return TREXIO_READONLY;

  qmc_t* qmc = trexio_text_read_qmc((trexio_text_t*) file);
  if (qmc == NULL) return TREXIO_FAILURE;

  qmc->qmc_num = num;
  qmc->qmc_num_isSet = true;
  qmc->to_flush = 1;

  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_text_write_determinant_coefficient(trexio_t* const file,
                                                const int64_t offset_file,
                                                const uint32_t rank,
                                                const uint64_t* dims,
                                                const double* dset)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (dset == NULL) return TREXIO_INVALID_ARG_5;

  const char file_name[] = "/determinant_coefficient.txt";
  const int append_str_len = 6;

  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < dims[0]; ++i) {

    rc = fprintf(f, "%24.16e\n", *(dset+ i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }

  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", append_str_len);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRIu64 "\n", dims[0]);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Additional part for the trexio_text_has_group to work */
  const char group_file_name[] = "/determinant.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, group_file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(group_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_write_csf_coefficient(trexio_t* const file,
                                                const int64_t offset_file,
                                                const uint32_t rank,
                                                const uint64_t* dims,
                                                const double* dset)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (dset == NULL) return TREXIO_INVALID_ARG_5;

  const char file_name[] = "/csf_coefficient.txt";
  const int append_str_len = 6;

  /* The full path to the destination TXT file with sparse data. This will include TREXIO directory name. */
  char file_full_path[TREXIO_MAX_FILENAME_LENGTH];
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(file_name));

  /* Open the file in "a" (append) mode to guarantee that no truncation happens upon consecutive writes */
  FILE* f = fopen(file_full_path, "a");
  if (f == NULL) return TREXIO_FILE_ERROR;

  /* Write the data in the file and check the return code of fprintf to verify that > 0 bytes have been written */
  int rc;
  for (uint64_t i=0UL; i < dims[0]; ++i) {

    rc = fprintf(f, "%24.16e\n", *(dset+ i));
    if (rc <= 0) {
      fclose(f);
      return TREXIO_FAILURE;
    }

  }

  /* Close the TXT file */
  rc = fclose(f);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Append .size to the file_full_path in order to write additional info about the written buffer of data */
  strncat(file_full_path, ".size", append_str_len);

  /* Open the new file in "a" (append) mode to append info about the buffer that has been just written */
  FILE *f_wSize = fopen(file_full_path, "a");
  if (f_wSize == NULL) return TREXIO_FILE_ERROR;

  /* Write the buffer_size */
  rc = fprintf(f_wSize, "%" PRIu64 "\n", dims[0]);
  if (rc <= 0) {
    fclose(f_wSize);
    return TREXIO_FAILURE;
  }

  /* Close the TXT file */
  rc = fclose(f_wSize);
  if (rc != 0) return TREXIO_FILE_ERROR;

  /* Additional part for the trexio_text_has_group to work */
  const char group_file_name[] = "/csf.txt";

  memset (file_full_path, 0, TREXIO_MAX_FILENAME_LENGTH);
  /* Copy directory name in file_full_path */
  strncpy (file_full_path, file->file_name, TREXIO_MAX_FILENAME_LENGTH);
  file_full_path[TREXIO_MAX_FILENAME_LENGTH-1] = '\0';
  /* Append name of the file with sparse data */
  strncat (file_full_path, group_file_name, TREXIO_MAX_FILENAME_LENGTH - sizeof(group_file_name));

  bool file_exists = trexio_text_file_exists(file_full_path);

  /* Create an empty file for the trexio_text_has_group to work */
  if (!file_exists) {
    FILE *fp = fopen(file_full_path, "ab+");
    fclose(fp);
  }

  /* Exit upon success */
  return TREXIO_SUCCESS;
}

