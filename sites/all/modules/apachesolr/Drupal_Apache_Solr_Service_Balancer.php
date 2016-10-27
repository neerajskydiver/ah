<?php
require_once 'SolrPhpClient/Apache/Solr/Service/Balancer.php';

class Drupal_Apache_Solr_Service_Balancer extends Apache_Solr_Service_Balancer {

  /**
   * Get found read service for current PHP script execution.
   * 
   * @param boolean $random = FALSE
   *   Set to TRUE to get a random server without ping.
   * 
   * @return Drupal_Apache_Solr_Service
   *   Service instance
   */
  public function getReadService($random = FALSE) {
    // TODO implement random
    return $this->_selectReadService();
  }

  /**
   * Get found write service for current PHP script execution.
   * 
   * @param boolean $random = FALSE
   *   Set to TRUE to get a random server without ping.
   *
   * @return Drupal_Apache_Solr_Service
   *   Service instance
   */
  public function getWriteService($random = FALSE) {
    // TODO implement random
    return $this->_selectWriteService();
  }
  
  /**
   * Get summary information about the first index servive found.
   */
  public function getStatsSummary() {
    $service = $this->_selectWriteService();

    do {
      try {
        return $service->getStatsSummary();
      }
      catch (Exception $e) {
        if ($e->getCode() != 0) { //IF NOT COMMUNICATION ERROR
          throw $e;
        }
      }
      $service = $this->_selectWriteService(TRUE);
    } while ($service);
    
    return FALSE;
  }
  
  /**
   * Clear cached Solr data.
   */
  public function clearCache() {
    foreach ($this->_readableServices as $service) {
      @$service->clearCache;
    }
    foreach ($this->_writableServices as $service) {
      @$service->clearCache;
    }
  }
  
  /**
   * Get meta-data about the index.
   */
  public function getLuke($num_terms = 0) {
    $service = $this->_selectWriteService();

    do {
      try {
        return $service->getLuke($num_terms);
      }
      catch (Exception $e) {
        if ($e->getCode() != 0) { //IF NOT COMMUNICATION ERROR
          throw $e;
        }
      }
      $service = $this->_selectWriteService(TRUE);
    } while ($service);

    return FALSE;
  }
  /**
   * Get just the field meta-data about the index.
   */
  public function getFields($num_terms = 0) {
    return $this->getLuke($num_terms)->fields;
  }
  
  /**
   * For some reasons this was not implemented in Balancer.
   */
  public function deleteByMultipleIds($ids, $fromPending = true, $fromCommitted = true, $timeout = 3600) {
    $service = $this->_selectWriteService();

    do {
      try {
        return $service->deleteByMultipleIds($ids, $fromPending = true, $fromCommitted = true, $timeout = 3600);
      }
      catch (Exception $e) {
        if ($e->getCode() != 0) { //IF NOT COMMUNICATION ERROR
          throw $e;
        }
      }
      $service = $this->_selectWriteService(TRUE);
    } while ($service); 

    return FALSE;
  }
  
  /**
   * Check if an index or query server is vailable.
   */
  public function ping($timeout = 2, $service_type) {
    $service = $service_type == 'index' ? $this->_selectWriteService() : $this->_selectReadService();

    do {
      try {
        return $service->ping($timeout);
      }
      catch (Exception $e) {
        if ($e->getCode() != 0) { //IF NOT COMMUNICATION ERROR
          throw $e;
        }
      }
      $service = $service_type == 'index' ? $this->_selectWriteService(TRUE) : $this->_selectReadService(TRUE);
    } while ($service);

    return FALSE;
  }
}
