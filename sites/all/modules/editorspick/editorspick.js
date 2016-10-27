/* Created date : 07 March 2011
*  Created by : Akshay Sardar
*  Aim : To avoid autocomplete slashes issues for articles 
*/

$(document).ready(function() {
	Drupal.ACDB.prototype._search = Drupal.ACDB.prototype.search;	
	Drupal.ACDB.prototype.search = function (searchString) {
	this._search(searchString.replace(/\//g, '~$~$~$~'));
	}
});