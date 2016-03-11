
---
layout: post
title: "A Spark Tutorial"
---

# Introduction
## What
[Apache Spark](https://spark.apache.org/) is an open source cluster computing framework. It aims to make it simpler to write programs that run in parallel across many nodes in a cluster of computers. It also provides a higher level API to work with distributed data. It is similar to other ditributed processing frameworks such as [Apache Hadoop](http://hadoop.apache.org/); however, the underlying architecture is somewhat different.

You can check out this [page](http://spark.apache.org/community.html#history) for more background on Spark.
## Why
As declared on its webpage, Spark
> Run programs up to 100x faster than Hadoop MapReduce in memory, or 10x faster on disk.

In addition

* You can write Spark applications quickly in either Java, Scala, Python or R.
* You can combine SQL, machine learning ([MLlib](https://spark.apache.org/mllib/)), graph computation([GraphX](https://spark.apache.org/graphx/)) and Spark Streaming seamlessly in the same application.
* You can run Spark either on your own computer, on Hadoop YARN, on Apache Mesos, or in the cloud ([Amazon EC2](https://aws.amazon.com/ec2/), [Amazon EMR](https://aws.amazon.com/elasticmapreduce/)).
* Everyone is using it! Check out this [page](https://cwiki.apache.org/confluence/display/SPARK/Powered+By+Spark) for a list of companies and organizations creating products and projects for use with Apache Spark.

## How
Spark runs in four modes: (1) the standalone local mode; (2) the standalone cluster mode; (3) using [Mesos](http://mesos.apache.org/); (4) Using [YARN (Hadoop NextGen)](http://hadoop.apache.org/docs/stable/hadoop-yarn/hadoop-yarn-site/YARN.html). In this post, I will introduce how to set up the standalone local mode on your own computer.

* First, you need to have [Java](https://java.com/en/download/manual.jsp) installed on your computer.
* Download the [Spark binaries](http://spark.apache.org/downloads.html). A package pre-built for Hadoop is recommended unless you want to build Spark against a specific Hadoop version. Save the unziped files in, for example, **C:\spark**. Try run **C:\spark\bin\spark-shell.cmd** which may produce some errors if you are using Windows (see next step to solve this problem).
```bash
cd C:\spark\bin
spark-shell
```
* Windows users:
    * Make sure **C:\Windows\System32** is in PATH in environment variables.
    * [Download](https://github.com/steveloughran/winutils/raw/master/hadoop-2.6.0/bin/winutils.exe) the 64-bit **winutils.exe**, save **winutils.exe** into a folder like **C:\hadoop\bin** and set your environment variable `HADOOP_HOME` to **C:\hadoop** (NOT C:\hadoop\bin).
    ```bash
    set HADOOP_HOME=C:\hadoop
    echo %HADOOP_HOME%
    ```
    * Set permision to **C:\tmp\hive**, which is created by Hive when starting the **spark-shell.cmd**.
    ```bash
    %HADOOP_HOME%\bin\winutils.exe chmod 777 \tmp\hive
    %HADOOP_HOME%\bin\winutils.exe ls \tmp\hive
    ```
* Now, re-run the **spark-shell.cmd** and it should work as expected.
* You can run the example to test the successful setup.
```bash
run-example org.apache.spark.examples.SparkPi
```
If everything goes well, you should see something similar to
```
16/03/10 20:25:51 INFO DAGScheduler: Job 0 finished: reduce at SparkPi.scala:36, took 1.596556 s
Pi is roughly 3.14358
```
