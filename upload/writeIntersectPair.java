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
import java.io.InputStreamReader;
 

public class writeIntersectPair {
  public static void main(String[] args) {
    DB db;
    String line = "";
    try {
      MongoClient mongoClient = new MongoClient( "nfs011" , 27015 );
      db = mongoClient.getDB( "tcga_segmentation" );
      DBCollection  coll = db.getCollection("results");
      
      BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
      
      String id_1, id_2;
      Integer tile_id;
      
      while ((line = in.readLine()) != null && line.length() != 0) {
        //System.out.println(s+"haha");
        String[] tmp = line.split("\t");
        if (tmp.length < 7)  continue;
        id_1 = tmp[0];
        id_2 = tmp[1];
        tile_id = Integer.parseInt(tmp[6]);
               
        BasicDBObject wdoc = new BasicDBObject("heatmap_id", args[1]+":"+args[2])
          .append("algorithm1_id", args[1])
          .append("algorithm2_id", args[2])
          .append("tile_id", tile_id)
	  .append("poly1_obj_id", id_1)
          .append("poly2_obj_id", id_2)
          .append("image_caseid", args[0]);
        
        /*System.out.println(wdoc.toString());
        db = mongoClient.getDB( "testing" );
        boolean collectionExists = db.collectionExists("results");
        if (collectionExists == false) {
          db.createCollection("results", null);
        }
        coll = db.getCollection("results");*/
        coll.insert(wdoc);
      }
      in.close();
    } catch (Exception e) {
      System.out.println(e.toString());
      System.out.println(line.length());
      System.out.println("error in "+line);
      return;
    } 
  }
}

