---
layout: post
title: "Spark Study Note I: Setting Up"
---

It is always fun to learn new things. In this and the following posts, I will write down the study notes on how I play around with Apache Spark on my own laptop. Many of the resources come from the book [Machine Learning with Spark](https://books.google.com/books?id=syPHBgAAQBAJ&source=gbs_navlinks_s).

[Apache Spark](https://spark.apache.org/) is an open source cluster computing framework. It aims to make it simpler to write programs that run in parallel across many nodes in a cluster of computers. It also provides a higher level API to work with distributed data. It is similar to other ditributed processing frameworks such as [Apache Hadoop](http://hadoop.apache.org/); however, the underlying architecture is somewhat different.

![png](https://upload.wikimedia.org/wikipedia/commons/e/ea/Spark-logo-192x100px.png)

You can check out this [page](http://spark.apache.org/community.html#history) for more background on Spark.

## Why Spark?
Quoted from its webpage, Spark

> Run programs up to 100x faster than Hadoop MapReduce in memory, or 10x faster on disk.

In addition

* You can write Spark applications quickly in either Java, Scala, Python or R.
* You can combine SQL, machine learning ([MLlib](https://spark.apache.org/mllib/)), graph computation([GraphX](https://spark.apache.org/graphx/)) and Spark Streaming seamlessly in the same application.
* You can run Spark either on your own computer, on Hadoop YARN, on Apache Mesos, or in the cloud ([Amazon EC2](http://spark.apache.org/docs/0.7.0/ec2-scripts.html), [Amazon EMR](http://aws.amazon.com/articles/Elastic-MapReduce/4926593393724923)).
* Everyone is using it! Check out this [list](https://cwiki.apache.org/confluence/display/SPARK/Powered+By+Spark) of companies and organizations creating products and projects for use with Apache Spark.

## Setting up Spark locally
Spark runs in four modes: (1) the standalone local mode; (2) the standalone cluster mode; (3) using [Mesos](http://mesos.apache.org/); (4) Using [YARN (Hadoop NextGen)](http://hadoop.apache.org/docs/stable/hadoop-yarn/hadoop-yarn-site/YARN.html). In this post, I will introduce how to set up the standalone local mode on your own computer.

First, you need to have [Java](https://java.com/en/download/manual.jsp) installed on your computer.

Download the [Spark binaries](http://spark.apache.org/downloads.html). A package pre-built for Hadoop is recommended unless you want to build Spark against a specific Hadoop version. Save the unziped files in, for example, `C:\spark`. Try run `spark\bin\spark-shell.cmd` which may produce some errors if you are using Windows (see below to solve this problem).

{% highlight bash %}
cd C:\spark\bin
spark-shell
{% endhighlight %}

Windows users:

* Make sure `Windows\System32` is in `PATH` in environment variables.
* [Download](https://github.com/steveloughran/winutils/raw/master/hadoop-2.6.0/bin/winutils.exe) the 64-bit `winutils.exe`, save it into a folder like `C:\hadoop\bin` and set environment variable `HADOOP_HOME` to `hadoop` (NOT `hadoop\bin`). Also, set permision to `tmp\hive`, which is created by Hive when starting the `spark-shell.cmd`.
    
{% highlight bash %}
set HADOOP_HOME=C:\hadoop
echo %HADOOP_HOME%
%HADOOP_HOME%\bin\winutils.exe chmod 777 \tmp\hive
%HADOOP_HOME%\bin\winutils.exe ls \tmp\hive
{% endhighlight %}

Now, re-run the `spark-shell.cmd` and it should work as expected. You can run the `run-example.cmd` under `spark\bin` to test the successful setup.

{% highlight bash %}
run-example org.apache.spark.examples.SparkPi
{% endhighlight %}

If everything goes well, you should see something similar to

{% highlight text %}
16/03/10 20:25:51 INFO DAGScheduler: Job 0 finished: reduce at SparkPi.scala:36, took 1.596556 s
Pi is roughly 3.14358
{% endhighlight %}

## Working with Python
The `bin\pyspark` script launches a Python interpreter that is configured to run PySpark applications.

{% highlight bash %}
pyspark
{% endhighlight %}

It is also possible to launch PySpark in IPython Notebook:

{% highlight bash %}
PYSPARK_DRIVER_PYTHON=ipython PYSPARK_DRIVER_PYTHON_OPTS='notebook' pyspark
{% endhighlight %}

Windows users:

{% highlight bash %}
set PYSPARK_DRIVER_PYTHON=ipython
set PYSPARK_DRIVER_PYTHON_OPTS='notebook'
pyspark
{% endhighlight %}

## Working with R
The `bin\sparkR` script launches R in command prompt (make sure `.\R\R-3.2.3\bin\x64` is in `PATH` in environment variables).

{% highlight bash %}
sparkR
{% endhighlight %}

It is also possible to start up sparkR from RStudio. The first few lines of code set the system environment variable `SPARK_HOME` to the path of your Spark folder.

{% highlight r %}
if (nchar(Sys.getenv("SPARK_HOME")) < 1) {
  Sys.setenv(SPARK_HOME = "/home/spark")
}

library(SparkR, lib.loc = c(file.path(Sys.getenv("SPARK_HOME"), "R", "lib")))
sc <- sparkR.init(master = "local[*]", sparkEnvir = list(spark.driver.memory="2g"))
sqlContext <- sparkRSQL.init(sc)

# check using the faithful dataset
df <- createDataFrame(sqlContext, faithful)
head(df)
{% endhighlight %}
