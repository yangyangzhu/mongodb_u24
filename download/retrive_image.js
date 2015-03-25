/**
 *  query : connect to tcga_segmentation collection and retrive data
 *          by 'analysis_execution_id' and 'image.caseid',
 *          then read the points data, and parser them into WKT format,
 *          add an index starting from 1 to mark the record number
 *  author: Yangyang Zhu (yangyang.zhu@stonybrook.edu)
 *  time  : 2/10/2015
 */

function query() {
  db = db.getSiblingDB('tcga_segmentation');

  var results = db.results.find(
    {
      analysis_execution_id : execution_id,
      'image.caseid' : image,  
    }
  );
  /*results.forEach( printjson );*/
  var j;
  var doc, width, heigth, points, output;
  while (results.hasNext()) {
    doc = results.next();
    width = doc.image.width;
    heigth = doc.image.heigth;
    points = doc.points;
    points = points.trim().split(/[\s,]+/);

    output = doc._id.str + '\t' + 'POLYGON ((';
    if (points.length > 1)
      output = output + Number(points[0]) * width + ' ' + Number(points[1]) * heigth; 
    for (j = 2; j < points.length; j++) {
      output = output + ',' + Number(points[j]) * width + ' ';
      j = j + 1; 
      output = output + Number(points[j]) * heigth;
    }
    /*if (execution_id == '/liz:vanner:sbu_definiens:2-13-2105/vanner/sbu_definiens/2-13-2015/00:00:00')
      output = output + ',' + Number(points[0]) * width + ' ' + Number(points[1]) * heigth; */
    output = output + '))'
    
    print(output);
  }
}
query();

