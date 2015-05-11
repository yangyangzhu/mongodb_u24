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


public class writeMetadata {
  public static void main(String[] args) {
    DB db;
    try {
      MongoClient mongoClient = new MongoClient( "nfs011" , 27015 );
      db = mongoClient.getDB( "u24_segmentation" );

      DBCollection coll = db.getCollection("metadata");

      BasicDBObject wdoc = new BasicDBObject("caseid", args[0])
        .append("analysis_execution_id", args[1])
        .append("title", args[2]);

        //System.out.println(wdoc.toString());
        /*db = mongoClient.getDB( "testing" );
        boolean collectionExists = db.collectionExists("results");
        if (collectionExists == false) {
          db.createCollection("results", null);
        }
        coll = db.getCollection("results");
      */
      coll.insert(wdoc);
    } catch (Exception e) {
      System.out.println(e.toString());
      return;
    } 
  }
}
