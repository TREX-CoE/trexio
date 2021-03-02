/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#include "trexio_text.h"

trexio_exit_code trexio_text_init(trexio_t* file) {

  trexio_text_t* f = (trexio_text_t*) file;

  /* If directory doesn't exist, create it */
  struct stat st;
  
  if (stat(file->file_name, &st) == 0 && S_ISDIR(st.st_mode)) {
    /* Do nothing */
  } else {
    if (mkdir(file->file_name, 0777) != 0) {
      return TREXIO_FAILURE;
    }
  }  

  /* Create name of files in the directory */
  const char* nucleus_file_name = "/nucleus.txt";
  f->nucleus_file_name = (char*)
    calloc( strlen(file->file_name) + strlen(nucleus_file_name) + 1,
            sizeof(char));
  assert (f->nucleus_file_name != NULL);
  strcpy (f->nucleus_file_name, file->file_name);
  strcat (f->nucleus_file_name, nucleus_file_name);


  const char* electron_file_name = "/electron.txt";
  f->electron_file_name = (char*)
    calloc( strlen(file->file_name) + strlen(electron_file_name) + 1,
            sizeof(char));
  assert (f->electron_file_name != NULL);
  strcpy (f->electron_file_name, file->file_name);
  strcat (f->electron_file_name, electron_file_name);

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_finalize(trexio_t* file) {

  trexio_text_t* f = (trexio_text_t*) file;

  free (f->nucleus_file_name);
  f->nucleus_file_name = NULL;

  free (f->electron_file_name);
  f->electron_file_name = NULL;

  return TREXIO_SUCCESS;
}

nucleus_t* trexio_text_read_nucleus(const trexio_text_t* file) {

  /* Allocate the data structure */
  nucleus_t* nucleus = (nucleus_t*) malloc(sizeof(nucleus_t));
  assert (nucleus != NULL);

  nucleus->num    = 0;
  nucleus->coord  = NULL;
  nucleus->charge = NULL;

  /* Try to open the file. If the file does not exist, return */
  FILE* f = fopen(file->nucleus_file_name,"r");
  if (f == NULL) {
    return nucleus;
  }

  /* Find size of file to allocate the max size of the string buffer */
  fseek(f, 0L, SEEK_END);
  size_t sz = ftell(f);
  fseek(f, 0L, SEEK_SET);
  char* buffer = (char*) malloc(sz*sizeof(char));

  /* Read the dimensioning variables */
  fscanf(f, "%s", buffer);
  assert (strcmp(buffer, "num") == 0);

  fscanf(f, "%lu", &(nucleus->num));
  assert (nucleus->num > 0);

  /* Allocate arrays */
  nucleus->charge = (double*) calloc(nucleus->num, sizeof(double));
  assert (nucleus->charge != NULL);
  
  nucleus->coord = (double*) calloc(3 * nucleus->num, sizeof(double));
  assert (nucleus->coord != NULL);

  /* Read arrays */
  fscanf(f, "%s", buffer);
  assert (strcmp(buffer, "charge") == 0);

  for (size_t i=0 ; i<nucleus->num ; i++) {
    fscanf(f, "%lf", &(nucleus->charge[i]));
  }
  
  fscanf(f, "%s", buffer);
  assert (strcmp(buffer, "coord") == 0);

  for (size_t i=0 ; i<3*nucleus->num ; i++) {
      fscanf(f, "%lf", &(nucleus->coord[i]));
  }
  free(buffer);
  fclose(f);
  return nucleus;
}


trexio_exit_code trexio_text_write_nucleus(const trexio_text_t* file, nucleus_t* nucleus) {
  assert (nucleus != NULL);

  FILE* f = fopen(file->nucleus_file_name,"w");
  assert (f != NULL);

  /* Write the dimensioning variables */
  fprintf(f, "num %ld\n", nucleus->num);

  /* Write arrays */
  fprintf(f, "charge\n");
  for (size_t i=0 ; i<nucleus->num ; i++) {
    fprintf(f, "%lf\n", nucleus->charge[i]);
  }

  fprintf(f, "coord\n");
  for (size_t i=0 ; i<3*nucleus->num ; i++) {
      fprintf(f, "%lf\n", nucleus->coord[i]);
  }

  fclose(f);
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_free_nucleus(nucleus_t* nucleus) {
  
  if (nucleus == NULL) {
    return TREXIO_FAILURE;
  }
  
  if (nucleus->coord != NULL) {
    free (nucleus->coord);
  }
  nucleus->coord = NULL;
  
  if (nucleus->charge != NULL) {
    free (nucleus->charge);
  }
  nucleus->charge = NULL;
  
  free (nucleus);
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_nucleus_num(const trexio_t* file, uint64_t* num) {

  assert (file != NULL);
  assert (num  != NULL);

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  
  if (nucleus == NULL) {
    return TREXIO_FAILURE;
  }

  /**/ *num = nucleus->num;

  trexio_text_free_nucleus(nucleus);
  return TREXIO_SUCCESS;
}

 
trexio_exit_code trexio_text_write_nucleus_num(const trexio_t* file, const uint64_t num) {

  assert (num > 0L);
  assert (file != NULL);
  
  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);

  assert (nucleus != NULL);
  
  if (nucleus->num != num) {

    nucleus->num = num;

    if (nucleus->charge != NULL) free(nucleus->charge);
    nucleus->charge = NULL;

    nucleus->charge = (double*) calloc(num, sizeof(double));
    assert (nucleus->charge != NULL);
    
    if (nucleus->coord  != NULL) free(nucleus->coord );
    nucleus->coord = NULL;

    nucleus->coord = (double*) calloc(3*num, sizeof(double));
    assert (nucleus->coord != NULL);

  } else {
    nucleus->num = num;
  }
  
  trexio_exit_code rc = trexio_text_write_nucleus((trexio_text_t*) file, nucleus);
  assert (rc == TREXIO_SUCCESS);

  trexio_text_free_nucleus(nucleus);
  
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_nucleus_coord(const trexio_t* file, double* coord) {

  assert (file != NULL);
  assert (file != NULL);
  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  
  if (nucleus == NULL) {
    return TREXIO_FAILURE;
  }

  assert (coord != NULL);
  
  for (size_t i=0 ; i<3*nucleus->num ; i++) {
    coord[i] = nucleus->coord[i];
  }

  trexio_text_free_nucleus(nucleus);
  return TREXIO_SUCCESS;
}

 
trexio_exit_code trexio_text_write_nucleus_coord(const trexio_t* file, const double* coord) {

  assert (coord != NULL);
  assert (file != NULL);
  
  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  assert (nucleus != NULL);
  
  for (size_t i=0 ; i<3*nucleus->num ; i++) {
    nucleus->coord[i] = coord[i];
  }
  
  trexio_exit_code rc = trexio_text_write_nucleus((trexio_text_t*) file, nucleus);
  assert (rc == TREXIO_SUCCESS);

  trexio_text_free_nucleus(nucleus);
  
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_text_read_nucleus_charge(const trexio_t* file, double* charge) {

  assert (file != NULL);
  assert (file != NULL);
  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*)file);
  
  if (nucleus == NULL) {
    return TREXIO_FAILURE;
  }

  assert (charge != NULL);
  
  for (size_t i=0 ; i<nucleus->num ; i++) {
    charge[i] = nucleus->charge[i];
  }

  trexio_text_free_nucleus(nucleus);
  return TREXIO_SUCCESS;
}

 
trexio_exit_code trexio_text_write_nucleus_charge(const trexio_t* file, const double* charge) {

  assert (charge != NULL);
  assert (file != NULL);
  
  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*)file);
  assert (nucleus != NULL);
  
  for (size_t i=0 ; i<nucleus->num ; i++) {
    nucleus->charge[i] = charge[i];
  }
  
  trexio_exit_code rc = trexio_text_write_nucleus((trexio_text_t*) file, nucleus);
  assert (rc == TREXIO_SUCCESS);

  trexio_text_free_nucleus(nucleus);
  
  return TREXIO_SUCCESS;
}
