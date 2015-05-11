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


public class writeTilePolygon{
  public static void main(String[] args) {
    DB db;
    try {
      MongoClient mongoClient = new MongoClient( "nfs011" , 27015 );
      db = mongoClient.getDB( "tcga_segmentation" );

      DBCollection coll = db.getCollection("results");

      BufferedReader br = new BufferedReader(new FileReader(args[0]));
      String line;
      while ((line = br.readLine()) != null) { 
        String[] tmp = line.split("\t");

        Integer tile_id = Integer.parseInt(tmp[0]);
        Integer algorithm_id = Integer.parseInt(tmp[1]);
        String obj_id = tmp[3];
        String algorithm;
     
        if (algorithm_id == 1)   algorithm = args[1];
        else algorithm = args[2];
        

        BasicDBObject wdoc = new BasicDBObject("analysis_execution_id", args[3])
          .append("image_caseid", args[4])
          .append("tile_id", tile_id)
          .append("algorithm_id", algorithm)
          .append("poly_obj_id", obj_id);

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
