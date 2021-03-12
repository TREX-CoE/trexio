/* [[file:trexio_text.org::*File prefixes][File prefixes:4]] */
/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#include "trexio_text.h"
/* File prefixes:4 ends here */

/* [[file:trexio_text.org::*Init/deinit functions][Init/deinit functions:2]] */
trexio_exit_code trexio_text_init(trexio_t* file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  /* Put all pointers to NULL but leave parent untouched */
  memset(&(f->parent)+1,0,sizeof(trexio_text_t)-sizeof(trexio_t));

  /* If directory doesn't exist, create it in write mode */
  struct stat st;
  
  if (stat(file->file_name, &st) == 0 && S_ISDIR(st.st_mode)) {
    /* Do nothing */
  } else {
    if (file->mode == 'r') return TREXIO_READONLY;
    
    if (mkdir(file->file_name, 0777) != 0) {
      return TREXIO_FAILURE;
    }
  }  

  /* Create the lock file in the directory */
  const char* lock_file_name = "/.lock";
  char* file_name =
    CALLOC(strlen(file->file_name) + strlen(lock_file_name) + 1, char);

  if (file_name == NULL) {
    return TREXIO_ALLOCATION_FAILED;
  }
 
  strcpy (file_name, file->file_name);
  strcat (file_name, lock_file_name);

  f->lock_file = open(file_name,O_WRONLY|O_CREAT|O_TRUNC, 0644);
  FREE(file_name);

  if (f->lock_file <= 0) {
    return TREXIO_FAILURE;
  }

  return TREXIO_SUCCESS;
}
/* Init/deinit functions:2 ends here */

/* [[file:trexio_text.org::*Init/deinit functions][Init/deinit functions:4]] */
trexio_exit_code trexio_text_lock(trexio_t* file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

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
/* Init/deinit functions:4 ends here */

/* [[file:trexio_text.org::*Init/deinit functions][Init/deinit functions:6]] */
trexio_exit_code trexio_text_finalize(trexio_t* file) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  trexio_exit_code rc;
  rc = trexio_text_free_nucleus( (trexio_text_t*) file);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_text_free_rdm( (trexio_text_t*) file);
  assert (rc == TREXIO_SUCCESS);
  
  return TREXIO_SUCCESS;
}
/* Init/deinit functions:6 ends here */

/* [[file:trexio_text.org::*Init/deinit functions][Init/deinit functions:8]] */
trexio_exit_code trexio_text_unlock(trexio_t* file) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  trexio_text_t* f = (trexio_text_t*) file;

  struct flock fl;

  fl.l_type   = F_WRLCK;
  fl.l_whence = SEEK_SET;
  fl.l_start  = 0;         
  fl.l_len    = 0;         
  fl.l_pid    = getpid();  
  fl.l_type   = F_UNLCK;   
  fcntl(f->lock_file, F_SETLK, &fl);
    
  close(f->lock_file);
  return TREXIO_SUCCESS;
}
/* Init/deinit functions:8 ends here */

/* [[file:trexio_text.org::*Read the struct][Read the struct:2]] */
#define DEBUG printf("%s : line %d\n", __FILE__, __LINE__);

nucleus_t* trexio_text_read_nucleus(trexio_text_t* file) {
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
  const char* nucleus_file_name = "/nucleus.txt";
  char * file_name = (char*)
    calloc( strlen(file->parent.file_name) + strlen(nucleus_file_name) + 1,
            sizeof(char));

  if (file_name == NULL) {
    FREE(nucleus);
DEBUG
    return NULL;
  }
  
  strcpy (file_name, file->parent.file_name);
  strcat (file_name, nucleus_file_name);

  /* If the file exists, read it */
  FILE* f = fopen(file_name,"r");
  if (f != NULL) {
    
    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    char* buffer = CALLOC(sz,char);
    if (buffer == NULL) {
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    /* Read the dimensioning variables */
    int rc;

    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_charge") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(nucleus->rank_charge));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
     
    uint64_t size_charge = 1;
    for (uint i=0; i<nucleus->rank_charge; i++){

      uint j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_charge") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(nucleus->dims_charge[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus);
DEBUG
        return NULL;
      }

      size_charge *= nucleus->dims_charge[i];
    }
    
    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_coord") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(nucleus->rank_coord));
    assert(!(rc != 1));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
     
    uint64_t size_coord = 1;
    for (uint i=0; i<nucleus->rank_coord; i++){

      uint j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_coord") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus);
DEBUG
        return NULL;
      }
    
      rc = fscanf(f, "%lu", &(nucleus->dims_coord[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus);
DEBUG
        return NULL;
      }

      size_coord *= nucleus->dims_coord[i];
    }
    
    /* Allocate arrays */
    nucleus->charge = (double*) calloc(size_charge, sizeof(double));
    assert (!(nucleus->charge == NULL));
    if (nucleus->charge == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    nucleus->coord = (double*) calloc(size_coord, sizeof(double));
    assert (!(nucleus->coord == NULL));
    if (nucleus->coord == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus->charge);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    /* Read data */
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "num") != 0)));
    if ((rc != 1) || (strcmp(buffer, "num") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus->charge);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%lu", &(nucleus->num));
    assert(!(rc != 1));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus->charge);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "charge") != 0)));
    if ((rc != 1) || (strcmp(buffer, "charge") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus->charge);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_charge ; i++) {
      rc = fscanf(f, "%lf", &(nucleus->charge[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus->charge);
        FREE(nucleus);
DEBUG
        return NULL;
      }
    }
    
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "coord") != 0)));
    if ((rc != 1) || (strcmp(buffer, "coord") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus->charge);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_coord ; i++) {
      rc = fscanf(f, "%lf", &(nucleus->coord[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus->charge);
        FREE(nucleus);
DEBUG
        return NULL;
      }
    }
    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  if (file->parent.mode == 'w') {
    nucleus->file = fopen(file_name,"a");  
  } else { 
    nucleus->file = fopen(file_name,"r");  
  }
  FREE(file_name);
  assert (!(nucleus->file == NULL));
  if (nucleus->file == NULL) {
    FREE(nucleus->charge);
    FREE(nucleus);
DEBUG
    return NULL;
  }

  fseek(nucleus->file, 0L, SEEK_SET);
  file->nucleus = nucleus;
  return nucleus;
}
/* Read the struct:2 ends here */

/* [[file:trexio_text.org::*Flush the struct][Flush the struct:2]] */
trexio_exit_code trexio_text_flush_nucleus(const trexio_text_t* file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  nucleus_t* nucleus = file->nucleus;
  
  if (nucleus == NULL) return TREXIO_SUCCESS;

  if (nucleus->to_flush == 0) return TREXIO_SUCCESS;

  FILE* f = nucleus->file;
  assert (f != NULL);
  rewind(f);

  /* Write the dimensioning variables */ 
  fprintf(f, "rank_charge %d\n", nucleus->rank_charge);

  uint64_t size_charge = 1;
  for (uint i=0; i<nucleus->rank_charge; i++){
    fprintf(f, "dims_charge %d  %ld\n", i, nucleus->dims_charge[i]);
    size_charge *= nucleus->dims_charge[i];
  } 

  fprintf(f, "rank_coord %d\n", nucleus->rank_coord);

  uint64_t size_coord = 1;
  for (uint i=0; i<nucleus->rank_coord; i++){
    fprintf(f, "dims_coord %d  %ld\n", i, nucleus->dims_coord[i]);
    size_coord *= nucleus->dims_coord[i];
  } 

  /* Write arrays */
  fprintf(f, "num %ld\n", nucleus->num);
  fprintf(f, "charge\n");
  for (uint64_t i=0 ; i<size_charge ; i++) {
    fprintf(f, "%lf\n", nucleus->charge[i]);
  }

  fprintf(f, "coord\n");
  for (uint64_t i=0 ; i<size_coord ; i++) {
      fprintf(f, "%lf\n", nucleus->coord[i]);
  }
  fflush(f);
  file->nucleus->to_flush = 0;
  return TREXIO_SUCCESS;
}
/* Flush the struct:2 ends here */

/* [[file:trexio_text.org::*Free memory][Free memory:2]] */
trexio_exit_code trexio_text_free_nucleus(trexio_text_t* file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  
  trexio_exit_code rc;

  if (file->parent.mode != 'r') {
    rc = trexio_text_flush_nucleus(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  nucleus_t* nucleus = file->nucleus;
  if (nucleus == NULL) return TREXIO_SUCCESS;

  if (nucleus->file != NULL) {
    fclose(nucleus->file);
    nucleus->file = NULL;
  }

  if (nucleus->coord != NULL) {
    FREE (nucleus->coord);
  }
 
  if (nucleus->charge != NULL) {
    FREE (nucleus->charge);
  }
  
  FREE (nucleus);
  return TREXIO_SUCCESS;
}
/* Free memory:2 ends here */

/* [[file:trexio_text.org::*Read/Write the num attribute][Read/Write the num attribute:2]] */
trexio_exit_code trexio_text_read_nucleus_num(const trexio_t* file, uint64_t* num) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  /**/ *num = nucleus->num;

  return TREXIO_SUCCESS;
}

 
trexio_exit_code trexio_text_write_nucleus_num(const trexio_t* file, const uint64_t num) {

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->mode == 'r') return TREXIO_READONLY;
  
  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;
  
  nucleus->num = num;
  nucleus->to_flush = 1;
  
  return TREXIO_SUCCESS;
}
/* Read/Write the num attribute:2 ends here */

/* [[file:trexio_text.org::*Read/Write the coord attribute][Read/Write the coord attribute:2]] */
trexio_exit_code trexio_text_read_nucleus_coord(const trexio_t* file, double* coord, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (coord == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (rank != nucleus->rank_coord) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (uint i=0; i<rank; i++){
    if (dims[i] != nucleus->dims_coord[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    coord[i] = nucleus->coord[i];
  }

  return TREXIO_SUCCESS;
}

 
trexio_exit_code trexio_text_write_nucleus_coord(const trexio_t* file, const double* coord, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (coord == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;
  
  if (nucleus->coord != NULL) {
    FREE(nucleus->coord);
  }

  nucleus->rank_coord = rank;
  
  uint64_t dim_size = 1;
  for (uint i=0; i<nucleus->rank_coord; i++){
    nucleus->dims_coord[i] = dims[i];
    dim_size *= dims[i];
  }

  nucleus->coord = (double*) calloc(dim_size, sizeof(double));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    nucleus->coord[i] = coord[i];
  }
  
  nucleus->to_flush = 1;
  return TREXIO_SUCCESS;
}
/* Read/Write the coord attribute:2 ends here */

/* [[file:trexio_text.org::*Read/Write the charge attribute][Read/Write the charge attribute:2]] */
trexio_exit_code trexio_text_read_nucleus_charge(const trexio_t* file, double* charge, const uint32_t rank, const uint64_t* dims) {

  if (file   == NULL) return TREXIO_INVALID_ARG_1;
  if (charge == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (rank != nucleus->rank_charge) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (uint i=0; i<rank; i++){
    if (dims[i] != nucleus->dims_charge[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }
  
  for (uint64_t i=0 ; i<dim_size ; i++) {
    charge[i] = nucleus->charge[i];
  }

  return TREXIO_SUCCESS;
}

 
trexio_exit_code trexio_text_write_nucleus_charge(const trexio_t* file, const double* charge, const uint32_t rank, const uint64_t* dims) {
  if (file   == NULL)  return TREXIO_INVALID_ARG_1;
  if (charge == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;
  
  if (nucleus->charge != NULL) {
    FREE(nucleus->charge);
  }

  nucleus->rank_charge = rank;

  uint64_t dim_size = 1;
  for (uint i=0; i<nucleus->rank_charge; i++){
    nucleus->dims_charge[i] = dims[i];
    dim_size *= dims[i];
  }

  nucleus->charge = (double*) calloc(dim_size, sizeof(double));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    nucleus->charge[i] = charge[i];
  }
  
  nucleus->to_flush = 1;
  return TREXIO_SUCCESS;
}
/* Read/Write the charge attribute:2 ends here */

/* [[file:trexio_text.org::*Read the complete struct][Read the complete struct:2]] */
rdm_t* trexio_text_read_rdm(trexio_text_t* file) {
  if (file  == NULL) return NULL;

  if (file->rdm != NULL) return file->rdm;

  /* Allocate the data structure */
  rdm_t* rdm = MALLOC(rdm_t);
  assert (rdm != NULL);

  rdm->one_e           = NULL;
  rdm->two_e_file_name = NULL;
  rdm->file            = NULL;
  rdm->to_flush        = 0;

  /* Try to open the file. If the file does not exist, return */
  const char* rdm_file_name = "/rdm.txt";
  char * file_name = (char*)
    calloc( strlen(file->parent.file_name) + strlen(rdm_file_name) + 1,
            sizeof(char));
  assert (file_name != NULL);
  strcpy (file_name, file->parent.file_name);
  strcat (file_name, rdm_file_name);

  /* If the file exists, read it */
  FILE* f = fopen(file_name,"r");
  if (f != NULL) {
    
    /* Find size of file to allocate the max size of the string buffer */
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0L, SEEK_SET);
    char* buffer = CALLOC(sz,char);
    
    /* Read the dimensioning variables */
    int rc;
    rc = fscanf(f, "%s", buffer);
    assert (rc == 1);
    assert (strcmp(buffer, "dim_one_e") == 0);
    
    rc = fscanf(f, "%lu", &(rdm->dim_one_e));
    assert (rc == 1);
    
    /* Allocate arrays */
    rdm->one_e = (double*) calloc(rdm->dim_one_e, sizeof(double));
    assert (rdm->one_e != NULL);
    
    /* Read one_e */
    rc = fscanf(f, "%s", buffer);
    assert (rc == 1);
    assert (strcmp(buffer, "one_e") == 0);
    
    for (uint64_t i=0 ; i<rdm->dim_one_e; i++) {
      rc = fscanf(f, "%lf", &(rdm->one_e[i]));
      assert (rc == 1);
    }
    
    /* Read two_e */
    rc = fscanf(f, "%s", buffer);
    assert (rc == 1);
    assert (strcmp(buffer, "two_e_file_name") == 0);
    
    rc = fscanf(f, "%s", buffer);
    assert (rc == 1);
    rdm->two_e_file_name = CALLOC (strlen(buffer),char);
    strcpy(rdm->two_e_file_name, buffer);
    
    FREE(buffer);
    fclose(f);
    f = NULL;
  }
  if (file->parent.mode == 'w') {
    rdm->file = fopen(file_name,"a");  
  } else {
    rdm->file = fopen(file_name,"r");  
  }
  FREE(file_name);
  file->rdm = rdm ;
  return rdm;
}
/* Read the complete struct:2 ends here */

/* [[file:trexio_text.org::*Flush the complete struct][Flush the complete struct:2]] */
trexio_exit_code trexio_text_flush_rdm(const trexio_text_t* file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  rdm_t* rdm = file->rdm;
  if (rdm == NULL) return TREXIO_SUCCESS;

  if (rdm->to_flush == 0) return TREXIO_SUCCESS;

  FILE* f = rdm->file;
  assert (f != NULL);
  rewind(f);

  /* Write the dimensioning variables */
  fprintf(f, "num %ld\n", rdm->dim_one_e);

  /* Write arrays */
  fprintf(f, "one_e\n");
  for (uint64_t i=0 ; i< rdm->dim_one_e; i++) {
    fprintf(f, "%lf\n", rdm->one_e[i]);
  }

  fprintf(f, "two_e_file_name\n");
  fprintf(f, "%s\n", rdm->two_e_file_name);

  fflush(f);
  file->rdm->to_flush = 0;
  return TREXIO_SUCCESS;
}
/* Flush the complete struct:2 ends here */

/* [[file:trexio_text.org::*Free memory][Free memory:2]] */
trexio_exit_code trexio_text_free_rdm(trexio_text_t* file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  
  trexio_exit_code rc;
  if (file->parent.mode != 'r') {
    rc = trexio_text_flush_rdm(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  rdm_t* rdm = file->rdm;
  if (rdm == NULL) return TREXIO_SUCCESS;

  if (rdm->file != NULL) {
    fclose(rdm->file);
    rdm->file = NULL;
  }
  
  if (rdm->one_e != NULL) {
    FREE (rdm->one_e);
  }
  
  if (rdm->two_e_file_name != NULL) {
    FREE (rdm->two_e_file_name);
  }
  
  free (rdm);
  file->rdm = NULL;
  return TREXIO_SUCCESS;
}
/* Free memory:2 ends here */

/* [[file:trexio_text.org::*Read/Write the one_e attribute][Read/Write the one_e attribute:2]] */
trexio_exit_code trexio_text_read_rdm_one_e(const trexio_t* file, double* one_e, const uint64_t dim_one_e) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (one_e == NULL) return TREXIO_INVALID_ARG_2;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  if (dim_one_e != rdm->dim_one_e) return TREXIO_INVALID_ARG_3;

  for (uint64_t i=0 ; i<dim_one_e ; i++) {
    one_e[i] = rdm->one_e[i];
  }

  return TREXIO_SUCCESS;
}

 
trexio_exit_code trexio_text_write_rdm_one_e(const trexio_t* file, const double* one_e, const uint64_t dim_one_e) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (one_e == NULL)  return TREXIO_INVALID_ARG_2;
  if (file->mode != 'r') return TREXIO_READONLY;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;
  
  rdm->dim_one_e = dim_one_e;
  for (uint64_t i=0 ; i<dim_one_e ; i++) {
    rdm->one_e[i] = one_e[i];
  }
  
  rdm->to_flush = 1;
  return TREXIO_SUCCESS;
}
/* Read/Write the one_e attribute:2 ends here */

/* [[file:trexio_text.org::*Read/Write the two_e attribute][Read/Write the two_e attribute:2]] */
trexio_exit_code trexio_text_buffered_read_rdm_two_e(const trexio_t* file, const uint64_t offset, const uint64_t size, int64_t* index, double* value) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (index == NULL) return TREXIO_INVALID_ARG_4;
  if (value == NULL) return TREXIO_INVALID_ARG_5;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  FILE* f = fopen(rdm->two_e_file_name, "r");
  if (f == NULL) return TREXIO_END;

  const uint64_t line_length = 64;
  fseek(f, (long) offset * line_length, SEEK_SET);
  
  int rc;
  for (uint64_t i=0 ; i<size ; i++) {
    rc = fscanf(f, "%9ld %9ld %9ld %9ld %24le\n",
           &index[4*i], 
           &index[4*i+1], 
           &index[4*i+2], 
           &index[4*i+3], 
           &value[i]);
    if (rc == 5) {
      /* Do nothing */
    } else if (rc == EOF) {
      return TREXIO_END;
    } else if (rc == EOF) {
      return TREXIO_FAILURE;
    }
  }

  return TREXIO_SUCCESS;
}

 
trexio_exit_code trexio_text_buffered_write_rdm_two_e(const trexio_t* file, const uint64_t offset, const uint64_t size, const int64_t* index, const double* value) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (index == NULL) return TREXIO_INVALID_ARG_4;
  if (value == NULL) return TREXIO_INVALID_ARG_5;
  if (file->mode != 'r') return TREXIO_READONLY;

  rdm_t* rdm = trexio_text_read_rdm((trexio_text_t*) file);
  if (rdm == NULL) return TREXIO_FAILURE;

  FILE* f = fopen(rdm->two_e_file_name, "w");
  if (f == NULL) return TREXIO_FAILURE;

  const uint64_t line_length = 64;
  fseek(f, (long) offset * line_length, SEEK_SET);
  
  int rc;
  for (uint64_t i=0 ; i<size ; i++) {
    rc = fprintf(f, "%9ld %9ld %9ld %9ld %24le\n",
           index[4*i], 
           index[4*i+1], 
           index[4*i+2], 
           index[4*i+3], 
           value[i]);
    if (rc != 5) return TREXIO_FAILURE;
  }

  return TREXIO_SUCCESS;
}
/* Read/Write the two_e attribute:2 ends here */
