/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/


#include "trexio_text.h"

#define DEBUG printf("%s : line %d\n", __FILE__, __LINE__);
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
trexio_exit_code trexio_text_finalize(trexio_t* file) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;

  trexio_exit_code rc;
  //rc = trexio_text_free_nucleus( (trexio_text_t*) file);
  //rc = trexio_text_free_ecp( (trexio_text_t*) file);
  //assert (rc == TREXIO_SUCCESS);

  assert (trexio_text_free_nucleus( (trexio_text_t*) file) == TREXIO_SUCCESS);
  assert (trexio_text_free_ecp( (trexio_text_t*) file) == TREXIO_SUCCESS);

  rc = trexio_text_free_rdm( (trexio_text_t*) file);
  assert (rc == TREXIO_SUCCESS);
  
  return TREXIO_SUCCESS;
}
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
 

  if (nucleus->nucleus_charge != NULL) {
    FREE (nucleus->nucleus_charge);
  }
  

  if (nucleus->nucleus_coord != NULL) {
    FREE (nucleus->nucleus_coord);
  }
  
  
  FREE (nucleus);
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_free_ecp(trexio_text_t* file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  
  trexio_exit_code rc;

  if (file->parent.mode != 'r') {
    rc = trexio_text_flush_ecp(file);
    if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
  }

  ecp_t* ecp = file->ecp;
  if (ecp == NULL) return TREXIO_SUCCESS;

  if (ecp->file != NULL) {
    fclose(ecp->file);
    ecp->file = NULL;
  }
 

  if (ecp->ecp_lmax_plus_1 != NULL) {
    FREE (ecp->ecp_lmax_plus_1);
  }
  

  if (ecp->ecp_z_core != NULL) {
    FREE (ecp->ecp_z_core);
  }
  

  if (ecp->ecp_local_n != NULL) {
    FREE (ecp->ecp_local_n);
  }
  

  if (ecp->ecp_local_exponent != NULL) {
    FREE (ecp->ecp_local_exponent);
  }
  

  if (ecp->ecp_local_coef != NULL) {
    FREE (ecp->ecp_local_coef);
  }
  

  if (ecp->ecp_local_power != NULL) {
    FREE (ecp->ecp_local_power);
  }
  

  if (ecp->ecp_non_local_n != NULL) {
    FREE (ecp->ecp_non_local_n);
  }
  

  if (ecp->ecp_non_local_exponent != NULL) {
    FREE (ecp->ecp_non_local_exponent);
  }
  

  if (ecp->ecp_non_local_coef != NULL) {
    FREE (ecp->ecp_non_local_coef);
  }
  

  if (ecp->ecp_non_local_power != NULL) {
    FREE (ecp->ecp_non_local_power);
  }
  
  
  FREE (ecp);
  return TREXIO_SUCCESS;
}
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
    if ((rc != 1) || (strcmp(buffer, "rank_nucleus_charge") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(nucleus->rank_nucleus_charge));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }

    uint64_t size_nucleus_charge = 1;
    for (unsigned int i=0; i<nucleus->rank_nucleus_charge; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_nucleus_charge") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(nucleus->dims_nucleus_charge[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus);
DEBUG
        return NULL;
      }

      size_nucleus_charge *= nucleus->dims_nucleus_charge[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_nucleus_coord") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(nucleus->rank_nucleus_coord));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }

    uint64_t size_nucleus_coord = 1;
    for (unsigned int i=0; i<nucleus->rank_nucleus_coord; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_nucleus_coord") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(nucleus->dims_nucleus_coord[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(nucleus);
DEBUG
        return NULL;
      }

      size_nucleus_coord *= nucleus->dims_nucleus_coord[i];
    }



    /* Read data */
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "nucleus_num") != 0)));
    if ((rc != 1) || (strcmp(buffer, "nucleus_num") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
     
    rc = fscanf(f, "%lu", &(nucleus->nucleus_num));
    assert(!(rc != 1));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }

    
     
    /* Allocate arrays */
    nucleus->nucleus_charge = (double*) calloc(size_nucleus_charge, sizeof(double));
    assert (!(nucleus->nucleus_charge == NULL));
    if (nucleus->nucleus_charge == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "nucleus_charge") != 0)));
    if ((rc != 1) || (strcmp(buffer, "nucleus_charge") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(nucleus->nucleus_charge);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_nucleus_charge ; i++) {
      rc = fscanf(f, "%lf", &(nucleus->nucleus_charge[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(nucleus->nucleus_charge);
        FREE(nucleus);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    nucleus->nucleus_coord = (double*) calloc(size_nucleus_coord, sizeof(double));
    assert (!(nucleus->nucleus_coord == NULL));
    if (nucleus->nucleus_coord == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(nucleus);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "nucleus_coord") != 0)));
    if ((rc != 1) || (strcmp(buffer, "nucleus_coord") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(nucleus->nucleus_coord);
      FREE(nucleus);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_nucleus_coord ; i++) {
      rc = fscanf(f, "%lf", &(nucleus->nucleus_coord[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(nucleus->nucleus_coord);
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
    // TODO: free all dsets
    FREE(nucleus->nucleus_charge);
    FREE(nucleus->nucleus_coord);
    FREE(nucleus);
DEBUG
    return NULL;
  }

  fseek(nucleus->file, 0L, SEEK_SET);
  file->nucleus = nucleus;
  return nucleus;
}
ecp_t* trexio_text_read_ecp(trexio_text_t* file) {
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
  const char* ecp_file_name = "/ecp.txt";
  char * file_name = (char*)
    calloc( strlen(file->parent.file_name) + strlen(ecp_file_name) + 1,
            sizeof(char));

  if (file_name == NULL) {
    FREE(ecp);
DEBUG
    return NULL;
  }

  strcpy (file_name, file->parent.file_name);
  strcat (file_name, ecp_file_name);

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
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    /* Read the dimensioning variables */
    int rc;


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_lmax_plus_1") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_lmax_plus_1));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_lmax_plus_1 = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_lmax_plus_1; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_lmax_plus_1") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_lmax_plus_1[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_lmax_plus_1 *= ecp->dims_ecp_lmax_plus_1[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_z_core") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_z_core));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_z_core = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_z_core; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_z_core") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_z_core[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_z_core *= ecp->dims_ecp_z_core[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_local_n") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_local_n));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_local_n = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_local_n; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_local_n") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_local_n[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_local_n *= ecp->dims_ecp_local_n[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_local_exponent") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_local_exponent));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_local_exponent = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_local_exponent; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_local_exponent") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_local_exponent[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_local_exponent *= ecp->dims_ecp_local_exponent[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_local_coef") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_local_coef));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_local_coef = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_local_coef; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_local_coef") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_local_coef[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_local_coef *= ecp->dims_ecp_local_coef[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_local_power") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_local_power));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_local_power = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_local_power; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_local_power") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_local_power[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_local_power *= ecp->dims_ecp_local_power[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_non_local_n") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_non_local_n));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_non_local_n = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_non_local_n; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_non_local_n") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_non_local_n[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_non_local_n *= ecp->dims_ecp_non_local_n[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_non_local_exponent") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_non_local_exponent));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_non_local_exponent = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_non_local_exponent; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_non_local_exponent") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_non_local_exponent[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_non_local_exponent *= ecp->dims_ecp_non_local_exponent[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_non_local_coef") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_non_local_coef));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_non_local_coef = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_non_local_coef; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_non_local_coef") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_non_local_coef[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_non_local_coef *= ecp->dims_ecp_non_local_coef[i];
    }


    rc = fscanf(f, "%s", buffer);
    if ((rc != 1) || (strcmp(buffer, "rank_ecp_non_local_power") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    rc = fscanf(f, "%u", &(ecp->rank_ecp_non_local_power));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    uint64_t size_ecp_non_local_power = 1;
    for (unsigned int i=0; i<ecp->rank_ecp_non_local_power; i++){

      unsigned int j=-1;
      rc = fscanf(f, "%s %u", buffer, &j);
      if ((rc != 2) || (strcmp(buffer, "dims_ecp_non_local_power") != 0) || (j!=i)) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
          return NULL;
      }
    
      rc = fscanf(f, "%lu\n", &(ecp->dims_ecp_non_local_power[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
        FREE(ecp);
DEBUG
        return NULL;
      }

      size_ecp_non_local_power *= ecp->dims_ecp_non_local_power[i];
    }



    /* Read data */
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_local_num_n_max") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_local_num_n_max") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
     
    rc = fscanf(f, "%lu", &(ecp->ecp_local_num_n_max));
    assert(!(rc != 1));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }


    /* Read data */
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_non_local_num_n_max") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_non_local_num_n_max") != 0)) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
     
    rc = fscanf(f, "%lu", &(ecp->ecp_non_local_num_n_max));
    assert(!(rc != 1));
    if (rc != 1) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }

    
     
    /* Allocate arrays */
    ecp->ecp_lmax_plus_1 = (int64_t*) calloc(size_ecp_lmax_plus_1, sizeof(int64_t));
    assert (!(ecp->ecp_lmax_plus_1 == NULL));
    if (ecp->ecp_lmax_plus_1 == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_lmax_plus_1") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_lmax_plus_1") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_lmax_plus_1);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_lmax_plus_1 ; i++) {
      rc = fscanf(f, "%ld", &(ecp->ecp_lmax_plus_1[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_lmax_plus_1);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_z_core = (int64_t*) calloc(size_ecp_z_core, sizeof(int64_t));
    assert (!(ecp->ecp_z_core == NULL));
    if (ecp->ecp_z_core == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_z_core") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_z_core") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_z_core);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_z_core ; i++) {
      rc = fscanf(f, "%ld", &(ecp->ecp_z_core[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_z_core);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_local_n = (int64_t*) calloc(size_ecp_local_n, sizeof(int64_t));
    assert (!(ecp->ecp_local_n == NULL));
    if (ecp->ecp_local_n == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_local_n") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_local_n") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_local_n);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_local_n ; i++) {
      rc = fscanf(f, "%ld", &(ecp->ecp_local_n[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_local_n);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_local_exponent = (double*) calloc(size_ecp_local_exponent, sizeof(double));
    assert (!(ecp->ecp_local_exponent == NULL));
    if (ecp->ecp_local_exponent == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_local_exponent") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_local_exponent") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_local_exponent);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_local_exponent ; i++) {
      rc = fscanf(f, "%lf", &(ecp->ecp_local_exponent[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_local_exponent);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_local_coef = (double*) calloc(size_ecp_local_coef, sizeof(double));
    assert (!(ecp->ecp_local_coef == NULL));
    if (ecp->ecp_local_coef == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_local_coef") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_local_coef") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_local_coef);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_local_coef ; i++) {
      rc = fscanf(f, "%lf", &(ecp->ecp_local_coef[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_local_coef);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_local_power = (int64_t*) calloc(size_ecp_local_power, sizeof(int64_t));
    assert (!(ecp->ecp_local_power == NULL));
    if (ecp->ecp_local_power == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_local_power") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_local_power") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_local_power);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_local_power ; i++) {
      rc = fscanf(f, "%ld", &(ecp->ecp_local_power[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_local_power);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_non_local_n = (int64_t*) calloc(size_ecp_non_local_n, sizeof(int64_t));
    assert (!(ecp->ecp_non_local_n == NULL));
    if (ecp->ecp_non_local_n == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_non_local_n") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_non_local_n") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_non_local_n);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_non_local_n ; i++) {
      rc = fscanf(f, "%ld", &(ecp->ecp_non_local_n[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_non_local_n);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_non_local_exponent = (double*) calloc(size_ecp_non_local_exponent, sizeof(double));
    assert (!(ecp->ecp_non_local_exponent == NULL));
    if (ecp->ecp_non_local_exponent == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_non_local_exponent") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_non_local_exponent") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_non_local_exponent);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_non_local_exponent ; i++) {
      rc = fscanf(f, "%lf", &(ecp->ecp_non_local_exponent[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_non_local_exponent);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_non_local_coef = (double*) calloc(size_ecp_non_local_coef, sizeof(double));
    assert (!(ecp->ecp_non_local_coef == NULL));
    if (ecp->ecp_non_local_coef == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_non_local_coef") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_non_local_coef") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_non_local_coef);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_non_local_coef ; i++) {
      rc = fscanf(f, "%lf", &(ecp->ecp_non_local_coef[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_non_local_coef);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }

     
    /* Allocate arrays */
    ecp->ecp_non_local_power = (int64_t*) calloc(size_ecp_non_local_power, sizeof(int64_t));
    assert (!(ecp->ecp_non_local_power == NULL));
    if (ecp->ecp_non_local_power == NULL) {
      FREE(buffer);
      FREE(file_name);
      FREE(ecp);
DEBUG
      return NULL;
    }
 
    rc = fscanf(f, "%s", buffer);
    assert(!((rc != 1) || (strcmp(buffer, "ecp_non_local_power") != 0)));
    if ((rc != 1) || (strcmp(buffer, "ecp_non_local_power") != 0)) {
      FREE(buffer);
      FREE(file_name);
      // TODO: free all dsets
      FREE(ecp->ecp_non_local_power);
      FREE(ecp);
DEBUG
      return NULL;
    }
    
    for (uint64_t i=0 ; i<size_ecp_non_local_power ; i++) {
      rc = fscanf(f, "%ld", &(ecp->ecp_non_local_power[i]));
      assert(!(rc != 1));
      if (rc != 1) {
        FREE(buffer);
        FREE(file_name);
      // TODO: free all dsets
        FREE(ecp->ecp_non_local_power);
        FREE(ecp);
DEBUG
        return NULL;
      }
    }


    FREE(buffer);
    fclose(f);
    f = NULL;
  }

  if (file->parent.mode == 'w') {
    ecp->file = fopen(file_name,"a");  
  } else { 
    ecp->file = fopen(file_name,"r");  
  }
  FREE(file_name);
  assert (!(ecp->file == NULL));
  if (ecp->file == NULL) {
    // TODO: free all dsets
    FREE(ecp->ecp_lmax_plus_1);
    FREE(ecp->ecp_z_core);
    FREE(ecp->ecp_local_n);
    FREE(ecp->ecp_local_exponent);
    FREE(ecp->ecp_local_coef);
    FREE(ecp->ecp_local_power);
    FREE(ecp->ecp_non_local_n);
    FREE(ecp->ecp_non_local_exponent);
    FREE(ecp->ecp_non_local_coef);
    FREE(ecp->ecp_non_local_power);
    FREE(ecp);
DEBUG
    return NULL;
  }

  fseek(ecp->file, 0L, SEEK_SET);
  file->ecp = ecp;
  return ecp;
}
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
 
 
  fprintf(f, "rank_nucleus_charge %d\n", nucleus->rank_nucleus_charge);

  uint64_t size_nucleus_charge = 1;
  for (unsigned int i=0; i<nucleus->rank_nucleus_charge; i++){
    fprintf(f, "dims_nucleus_charge %d  %ld\n", i, nucleus->dims_nucleus_charge[i]);
    size_nucleus_charge *= nucleus->dims_nucleus_charge[i];
  } 

 
  fprintf(f, "rank_nucleus_coord %d\n", nucleus->rank_nucleus_coord);

  uint64_t size_nucleus_coord = 1;
  for (unsigned int i=0; i<nucleus->rank_nucleus_coord; i++){
    fprintf(f, "dims_nucleus_coord %d  %ld\n", i, nucleus->dims_nucleus_coord[i]);
    size_nucleus_coord *= nucleus->dims_nucleus_coord[i];
  } 



  fprintf(f, "nucleus_num %ld\n", nucleus->nucleus_num);


  
  /* Write arrays */
  
  fprintf(f, "nucleus_charge\n");
  for (uint64_t i=0 ; i<size_nucleus_charge ; i++) {
    fprintf(f, "%lf\n", nucleus->nucleus_charge[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "nucleus_coord\n");
  for (uint64_t i=0 ; i<size_nucleus_coord ; i++) {
    fprintf(f, "%lf\n", nucleus->nucleus_coord[i]);
  }


  fflush(f);
  file->nucleus->to_flush = 0;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_flush_ecp(const trexio_text_t* file) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->parent.mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = file->ecp;
  
  if (ecp == NULL) return TREXIO_SUCCESS;

  if (ecp->to_flush == 0) return TREXIO_SUCCESS;

  FILE* f = ecp->file;
  assert (f != NULL);
  rewind(f);

  /* Write the dimensioning variables */ 
 
 
  fprintf(f, "rank_ecp_lmax_plus_1 %d\n", ecp->rank_ecp_lmax_plus_1);

  uint64_t size_ecp_lmax_plus_1 = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_lmax_plus_1; i++){
    fprintf(f, "dims_ecp_lmax_plus_1 %d  %ld\n", i, ecp->dims_ecp_lmax_plus_1[i]);
    size_ecp_lmax_plus_1 *= ecp->dims_ecp_lmax_plus_1[i];
  } 

 
  fprintf(f, "rank_ecp_z_core %d\n", ecp->rank_ecp_z_core);

  uint64_t size_ecp_z_core = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_z_core; i++){
    fprintf(f, "dims_ecp_z_core %d  %ld\n", i, ecp->dims_ecp_z_core[i]);
    size_ecp_z_core *= ecp->dims_ecp_z_core[i];
  } 

 
  fprintf(f, "rank_ecp_local_n %d\n", ecp->rank_ecp_local_n);

  uint64_t size_ecp_local_n = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_local_n; i++){
    fprintf(f, "dims_ecp_local_n %d  %ld\n", i, ecp->dims_ecp_local_n[i]);
    size_ecp_local_n *= ecp->dims_ecp_local_n[i];
  } 

 
  fprintf(f, "rank_ecp_local_exponent %d\n", ecp->rank_ecp_local_exponent);

  uint64_t size_ecp_local_exponent = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_local_exponent; i++){
    fprintf(f, "dims_ecp_local_exponent %d  %ld\n", i, ecp->dims_ecp_local_exponent[i]);
    size_ecp_local_exponent *= ecp->dims_ecp_local_exponent[i];
  } 

 
  fprintf(f, "rank_ecp_local_coef %d\n", ecp->rank_ecp_local_coef);

  uint64_t size_ecp_local_coef = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_local_coef; i++){
    fprintf(f, "dims_ecp_local_coef %d  %ld\n", i, ecp->dims_ecp_local_coef[i]);
    size_ecp_local_coef *= ecp->dims_ecp_local_coef[i];
  } 

 
  fprintf(f, "rank_ecp_local_power %d\n", ecp->rank_ecp_local_power);

  uint64_t size_ecp_local_power = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_local_power; i++){
    fprintf(f, "dims_ecp_local_power %d  %ld\n", i, ecp->dims_ecp_local_power[i]);
    size_ecp_local_power *= ecp->dims_ecp_local_power[i];
  } 

 
  fprintf(f, "rank_ecp_non_local_n %d\n", ecp->rank_ecp_non_local_n);

  uint64_t size_ecp_non_local_n = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_non_local_n; i++){
    fprintf(f, "dims_ecp_non_local_n %d  %ld\n", i, ecp->dims_ecp_non_local_n[i]);
    size_ecp_non_local_n *= ecp->dims_ecp_non_local_n[i];
  } 

 
  fprintf(f, "rank_ecp_non_local_exponent %d\n", ecp->rank_ecp_non_local_exponent);

  uint64_t size_ecp_non_local_exponent = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_non_local_exponent; i++){
    fprintf(f, "dims_ecp_non_local_exponent %d  %ld\n", i, ecp->dims_ecp_non_local_exponent[i]);
    size_ecp_non_local_exponent *= ecp->dims_ecp_non_local_exponent[i];
  } 

 
  fprintf(f, "rank_ecp_non_local_coef %d\n", ecp->rank_ecp_non_local_coef);

  uint64_t size_ecp_non_local_coef = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_non_local_coef; i++){
    fprintf(f, "dims_ecp_non_local_coef %d  %ld\n", i, ecp->dims_ecp_non_local_coef[i]);
    size_ecp_non_local_coef *= ecp->dims_ecp_non_local_coef[i];
  } 

 
  fprintf(f, "rank_ecp_non_local_power %d\n", ecp->rank_ecp_non_local_power);

  uint64_t size_ecp_non_local_power = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_non_local_power; i++){
    fprintf(f, "dims_ecp_non_local_power %d  %ld\n", i, ecp->dims_ecp_non_local_power[i]);
    size_ecp_non_local_power *= ecp->dims_ecp_non_local_power[i];
  } 



  fprintf(f, "ecp_local_num_n_max %ld\n", ecp->ecp_local_num_n_max);


  fprintf(f, "ecp_non_local_num_n_max %ld\n", ecp->ecp_non_local_num_n_max);


  
  /* Write arrays */
  
  fprintf(f, "ecp_lmax_plus_1\n");
  for (uint64_t i=0 ; i<size_ecp_lmax_plus_1 ; i++) {
    fprintf(f, "%ld\n", ecp->ecp_lmax_plus_1[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_z_core\n");
  for (uint64_t i=0 ; i<size_ecp_z_core ; i++) {
    fprintf(f, "%ld\n", ecp->ecp_z_core[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_local_n\n");
  for (uint64_t i=0 ; i<size_ecp_local_n ; i++) {
    fprintf(f, "%ld\n", ecp->ecp_local_n[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_local_exponent\n");
  for (uint64_t i=0 ; i<size_ecp_local_exponent ; i++) {
    fprintf(f, "%lf\n", ecp->ecp_local_exponent[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_local_coef\n");
  for (uint64_t i=0 ; i<size_ecp_local_coef ; i++) {
    fprintf(f, "%lf\n", ecp->ecp_local_coef[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_local_power\n");
  for (uint64_t i=0 ; i<size_ecp_local_power ; i++) {
    fprintf(f, "%ld\n", ecp->ecp_local_power[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_non_local_n\n");
  for (uint64_t i=0 ; i<size_ecp_non_local_n ; i++) {
    fprintf(f, "%ld\n", ecp->ecp_non_local_n[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_non_local_exponent\n");
  for (uint64_t i=0 ; i<size_ecp_non_local_exponent ; i++) {
    fprintf(f, "%lf\n", ecp->ecp_non_local_exponent[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_non_local_coef\n");
  for (uint64_t i=0 ; i<size_ecp_non_local_coef ; i++) {
    fprintf(f, "%lf\n", ecp->ecp_non_local_coef[i]);
  }

  
  /* Write arrays */
  
  fprintf(f, "ecp_non_local_power\n");
  for (uint64_t i=0 ; i<size_ecp_non_local_power ; i++) {
    fprintf(f, "%ld\n", ecp->ecp_non_local_power[i]);
  }


  fflush(f);
  file->ecp->to_flush = 0;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_nucleus_charge(const trexio_t* file, double* nucleus_charge, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_charge == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (rank != nucleus->rank_nucleus_charge) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != nucleus->dims_nucleus_charge[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    nucleus_charge[i] = nucleus->nucleus_charge[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_nucleus_coord(const trexio_t* file, double* nucleus_coord, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_coord == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  if (rank != nucleus->rank_nucleus_coord) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != nucleus->dims_nucleus_coord[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    nucleus_coord[i] = nucleus->nucleus_coord[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_lmax_plus_1(const trexio_t* file, int64_t* ecp_lmax_plus_1, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_lmax_plus_1 == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_lmax_plus_1) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_lmax_plus_1[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_lmax_plus_1[i] = ecp->ecp_lmax_plus_1[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_z_core(const trexio_t* file, int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_z_core == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_z_core) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_z_core[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_z_core[i] = ecp->ecp_z_core[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_local_n(const trexio_t* file, int64_t* ecp_local_n, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_n == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_local_n) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_local_n[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_local_n[i] = ecp->ecp_local_n[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_local_exponent(const trexio_t* file, double* ecp_local_exponent, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_exponent == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_local_exponent) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_local_exponent[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_local_exponent[i] = ecp->ecp_local_exponent[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_local_coef(const trexio_t* file, double* ecp_local_coef, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_coef == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_local_coef) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_local_coef[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_local_coef[i] = ecp->ecp_local_coef[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_local_power(const trexio_t* file, int64_t* ecp_local_power, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_power == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_local_power) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_local_power[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_local_power[i] = ecp->ecp_local_power[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_non_local_n(const trexio_t* file, int64_t* ecp_non_local_n, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_n == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_non_local_n) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_non_local_n[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_non_local_n[i] = ecp->ecp_non_local_n[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_non_local_exponent(const trexio_t* file, double* ecp_non_local_exponent, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_exponent == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_non_local_exponent) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_non_local_exponent[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_non_local_exponent[i] = ecp->ecp_non_local_exponent[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_non_local_coef(const trexio_t* file, double* ecp_non_local_coef, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_coef == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_non_local_coef) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_non_local_coef[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_non_local_coef[i] = ecp->ecp_non_local_coef[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_non_local_power(const trexio_t* file, int64_t* ecp_non_local_power, const uint32_t rank, const uint64_t* dims) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_power == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  if (rank != ecp->rank_ecp_non_local_power) return TREXIO_INVALID_ARG_3;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<rank; i++){
    if (dims[i] != ecp->dims_ecp_non_local_power[i]) return TREXIO_INVALID_ARG_4;
    dim_size *= dims[i];
  }

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp_non_local_power[i] = ecp->ecp_non_local_power[i];
  }

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_nucleus_num(const trexio_t* file, uint64_t* num) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;

  /**/ *num = nucleus->nucleus_num;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_local_num_n_max(const trexio_t* file, uint64_t* num) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  /**/ *num = ecp->ecp_local_num_n_max;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_read_ecp_non_local_num_n_max(const trexio_t* file, uint64_t* num) {

  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (num   == NULL) return TREXIO_INVALID_ARG_2;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;

  /**/ *num = ecp->ecp_non_local_num_n_max;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_nucleus_charge(const trexio_t* file, const double* nucleus_charge, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (nucleus_charge == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;
  
  if (nucleus->nucleus_charge != NULL) {
    FREE(nucleus->nucleus_charge);
  }

  nucleus->rank_nucleus_charge = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<nucleus->rank_nucleus_charge; i++){
    nucleus->dims_nucleus_charge[i] = dims[i];
    dim_size *= dims[i];
  }

  nucleus->nucleus_charge = (double*) calloc(dim_size, sizeof(double));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    nucleus->nucleus_charge[i] = nucleus_charge[i];
  }
  
  nucleus->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_nucleus_coord(const trexio_t* file, const double* nucleus_coord, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (nucleus_coord == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;
  
  if (nucleus->nucleus_coord != NULL) {
    FREE(nucleus->nucleus_coord);
  }

  nucleus->rank_nucleus_coord = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<nucleus->rank_nucleus_coord; i++){
    nucleus->dims_nucleus_coord[i] = dims[i];
    dim_size *= dims[i];
  }

  nucleus->nucleus_coord = (double*) calloc(dim_size, sizeof(double));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    nucleus->nucleus_coord[i] = nucleus_coord[i];
  }
  
  nucleus->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_lmax_plus_1(const trexio_t* file, const int64_t* ecp_lmax_plus_1, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_lmax_plus_1 == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_lmax_plus_1 != NULL) {
    FREE(ecp->ecp_lmax_plus_1);
  }

  ecp->rank_ecp_lmax_plus_1 = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_lmax_plus_1; i++){
    ecp->dims_ecp_lmax_plus_1[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_lmax_plus_1 = (int64_t*) calloc(dim_size, sizeof(int64_t));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_lmax_plus_1[i] = ecp_lmax_plus_1[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_z_core(const trexio_t* file, const int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_z_core == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_z_core != NULL) {
    FREE(ecp->ecp_z_core);
  }

  ecp->rank_ecp_z_core = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_z_core; i++){
    ecp->dims_ecp_z_core[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_z_core = (int64_t*) calloc(dim_size, sizeof(int64_t));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_z_core[i] = ecp_z_core[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_local_n(const trexio_t* file, const int64_t* ecp_local_n, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_local_n == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_local_n != NULL) {
    FREE(ecp->ecp_local_n);
  }

  ecp->rank_ecp_local_n = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_local_n; i++){
    ecp->dims_ecp_local_n[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_local_n = (int64_t*) calloc(dim_size, sizeof(int64_t));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_local_n[i] = ecp_local_n[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_local_exponent(const trexio_t* file, const double* ecp_local_exponent, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_local_exponent == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_local_exponent != NULL) {
    FREE(ecp->ecp_local_exponent);
  }

  ecp->rank_ecp_local_exponent = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_local_exponent; i++){
    ecp->dims_ecp_local_exponent[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_local_exponent = (double*) calloc(dim_size, sizeof(double));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_local_exponent[i] = ecp_local_exponent[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_local_coef(const trexio_t* file, const double* ecp_local_coef, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_local_coef == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_local_coef != NULL) {
    FREE(ecp->ecp_local_coef);
  }

  ecp->rank_ecp_local_coef = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_local_coef; i++){
    ecp->dims_ecp_local_coef[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_local_coef = (double*) calloc(dim_size, sizeof(double));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_local_coef[i] = ecp_local_coef[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_local_power(const trexio_t* file, const int64_t* ecp_local_power, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_local_power == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_local_power != NULL) {
    FREE(ecp->ecp_local_power);
  }

  ecp->rank_ecp_local_power = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_local_power; i++){
    ecp->dims_ecp_local_power[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_local_power = (int64_t*) calloc(dim_size, sizeof(int64_t));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_local_power[i] = ecp_local_power[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_non_local_n(const trexio_t* file, const int64_t* ecp_non_local_n, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_n == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_non_local_n != NULL) {
    FREE(ecp->ecp_non_local_n);
  }

  ecp->rank_ecp_non_local_n = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_non_local_n; i++){
    ecp->dims_ecp_non_local_n[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_non_local_n = (int64_t*) calloc(dim_size, sizeof(int64_t));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_non_local_n[i] = ecp_non_local_n[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_non_local_exponent(const trexio_t* file, const double* ecp_non_local_exponent, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_exponent == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_non_local_exponent != NULL) {
    FREE(ecp->ecp_non_local_exponent);
  }

  ecp->rank_ecp_non_local_exponent = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_non_local_exponent; i++){
    ecp->dims_ecp_non_local_exponent[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_non_local_exponent = (double*) calloc(dim_size, sizeof(double));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_non_local_exponent[i] = ecp_non_local_exponent[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_non_local_coef(const trexio_t* file, const double* ecp_non_local_coef, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_coef == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_non_local_coef != NULL) {
    FREE(ecp->ecp_non_local_coef);
  }

  ecp->rank_ecp_non_local_coef = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_non_local_coef; i++){
    ecp->dims_ecp_non_local_coef[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_non_local_coef = (double*) calloc(dim_size, sizeof(double));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_non_local_coef[i] = ecp_non_local_coef[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_non_local_power(const trexio_t* file, const int64_t* ecp_non_local_power, const uint32_t rank, const uint64_t* dims) {
  if (file  == NULL)  return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_power == NULL)  return TREXIO_INVALID_ARG_2;

  if (file->mode == 'r') return TREXIO_READONLY;

  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  if (ecp->ecp_non_local_power != NULL) {
    FREE(ecp->ecp_non_local_power);
  }

  ecp->rank_ecp_non_local_power = rank;
  
  uint64_t dim_size = 1;
  for (unsigned int i=0; i<ecp->rank_ecp_non_local_power; i++){
    ecp->dims_ecp_non_local_power[i] = dims[i];
    dim_size *= dims[i];
  }

  ecp->ecp_non_local_power = (int64_t*) calloc(dim_size, sizeof(int64_t));

  for (uint64_t i=0 ; i<dim_size ; i++) {
    ecp->ecp_non_local_power[i] = ecp_non_local_power[i];
  }
  
  ecp->to_flush = 1;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_nucleus_num(const trexio_t* file, const uint64_t num) {

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->mode == 'r') return TREXIO_READONLY;
  
  nucleus_t* nucleus = trexio_text_read_nucleus((trexio_text_t*) file);
  if (nucleus == NULL) return TREXIO_FAILURE;
  
  nucleus->nucleus_num = num;
  nucleus->to_flush = 1;
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_local_num_n_max(const trexio_t* file, const uint64_t num) {

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->mode == 'r') return TREXIO_READONLY;
  
  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  ecp->ecp_local_num_n_max = num;
  ecp->to_flush = 1;
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_text_write_ecp_non_local_num_n_max(const trexio_t* file, const uint64_t num) {

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  if (file->mode == 'r') return TREXIO_READONLY;
  
  ecp_t* ecp = trexio_text_read_ecp((trexio_text_t*) file);
  if (ecp == NULL) return TREXIO_FAILURE;
  
  ecp->ecp_non_local_num_n_max = num;
  ecp->to_flush = 1;
  
  return TREXIO_SUCCESS;
}
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
