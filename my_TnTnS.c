/*
 *Implementation of the test-and-test-and-set algorithm realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
 
void TnTnS_lock (TnTnS_t *mylock);
void TnTnS_unlock(TnTnS_t *mylock);