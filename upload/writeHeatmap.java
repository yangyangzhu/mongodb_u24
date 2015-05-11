import com.mongodb.BasicDBObject;
import com.mongodb.BulkWriteOperation;
import com.mongodb.BulkWriteResult;
import com.mongodb.Cursor;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;
import com.mongodb.ParallelScanOptions;
import com.mongodb.ServerAddress;

import java.util.List;
import java.util.Set;

import static java.util.concurrent.TimeUnit.SECONDS;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedReader;
import java.util.ArrayList;


public class writeHeatmap{
  public static void main(String[] args) {
    DB db;
    try {
      MongoClient mongoClient = new MongoClient( "nfs011" , 27015 );
      db = mongoClient.getDB( "u24_segmentation" );

      DBCollection coll = db.getCollection("results");
      BasicDBObject query = new BasicDBObject();
      query.put("analysis_execution_id", "vadim-alg:vadim-s48:thresh_post_mask");
      query.put("image.caseid", args[0]);
      DBObject doc = coll.findOne(query);
      DBObject image = (DBObject)doc.get("image");
      Double W = Double.parseDouble(image.get("width").toString());
      Double H = Double.parseDouble(image.get("heigth").toString());

      BufferedReader br = new BufferedReader(new FileReader(args[2]));
      String line;
      while ((line = br.readLine()) != null) { 
        String[] tmp = line.split(" |\t");

        Double stat = Double.parseDouble(tmp[0]);
        Integer tile_id = Integer.parseInt(tmp[1]);
        Double xmin = Double.parseDouble(tmp[2]);
        Double ymin = Double.parseDouble(tmp[3]);
        Double xmax = Double.parseDouble(tmp[4]);
        Double ymax = Double.parseDouble(tmp[5]);
        
        ArrayList<Double> al = new ArrayList<Double>();
        al.add(xmin/W);
        al.add(ymin/H);
     
        BasicDBObject features = new BasicDBObject("Area", (xmax - xmin)*(ymax - ymin))
          .append("Metric", stat)
          .append("MetricType", args[1]);

        BasicDBObject wdoc = new BasicDBObject("analysis_execution_id", args[3])
          .append("x", xmin/W)
          .append("tile_id", tile_id)
          .append("y", ymin/H)
          .append("loc", al)
          .append("w", (xmax-xmin)/W)
          .append("h", (ymax-ymin)/H)
          .append("normalized", new Boolean(true))
          .append("type", "heatmap")
          .append("color", "red")
          .append("features", features)
          .append("image", image);

        /*System.out.println(wdoc.toString());
        db = mongoClient.getDB( "testing" );
        boolean collectionExists = db.collectionExists("results");
        if (collectionExists == false) {
          db.createCollection("results", null);
        }
        coll = db.getCollection("results");
        */

        coll.insert(wdoc);
      }
      br.close();
     } catch (Exception e) {
      System.out.println(e.toString());
      return;
    } 
  }
}
