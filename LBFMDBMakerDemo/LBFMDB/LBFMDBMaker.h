//
//  LBFMDBMaker.h
//  Test
//
//  Created by 刘博 on 2018/4/27.
//  Copyright © 2018年 刘博. All rights reserved.
//
//此类是数据库操作的代理类，根据链式编程思想，将sql语句的动态生成、及数据库操作交由此类处理。
//目前只实现了简单的数据库操作(增删改查)，诸君可根据情况自行拓展。
//毕竟重点只是体现思路而已，因此会存在不完善，或者漏洞，望诸君见谅！
//目前只输出了简单的错误日志，还需结合FMDB的日志，结合进行调试。
//注：Warning: there is at least one open result set around after performing [FMDatabaseQueue inDatabase:]警告可忽略，因为此类只是通过resultSet属性存储了搜索结果而已，并未有其他操作。
//
//


#import <Foundation/Foundation.h>
#import "FMDatabaseQueue.h"
#import "FMDatabase.h"

@interface LBFMDBMaker : NSObject

@property(nonatomic,retain)FMDatabaseQueue * fmdbQueue;//当前maker操作的FMDatabaseQueue
@property(nonatomic,retain,readonly)NSMutableString* sqlString;//当前生成的sqlString
@property(nonatomic,retain,readonly)FMResultSet* resultSet;//查询数据库的检索结果
@property(nonatomic,retain,readonly)NSMutableArray * commons;//存储所生成的所有sql语句

/*
 *创建表
 *参数解释：
 *1.tableName:表名
 *2.properties:表属性名
 *3.propertyTypes:表属性类型(1=text,2=int,3=double)，可拓展，与.m文件的LBVALUE_TYPE对应
 *注：properties、propertyTypes需要一一对应
 */
-(LBFMDBMaker*(^)(NSString*tableName,NSArray<NSString*>* properties,NSArray* propertyTypes))Table;

/*
 *插入数据
 *参数解释：
 *1.tableName:表名
 *2.properties:表属性名
 *3.values:属性对应的值
 *注：properties、values需要一一对应
 */
-(LBFMDBMaker*(^)(NSString*tableName,NSArray<NSString*>* properties,NSArray* values))Insert;

/*
 *删除数据
 *参数解释：
 *1.tableName:表名
 *注：需要与Where配合使用，完善查询条件
 */
-(LBFMDBMaker*(^)(NSString*tableName))Delete;

/*
 *更新数据
 *参数解释：
 *1.tableName:表名
 *2.property:更新的属性
 *3.value:更新的值
 *注：需要与Where配合使用，完善查询条件
 */
-(LBFMDBMaker*(^)(NSString*tableName,NSString*property,id value))Update;

/*
 *查询条件
 *参数解释：
 *1.termStr:条件语句
 *注：需自行写正确的sql语句，例如查age属性为18的人，就听该传入"age = 18"
 */
-(LBFMDBMaker*(^)(NSString*termStr))Where;

/*
 *查询表
 *参数解释：
 *1.tableName:表名
 *注：可与Where配合使用
 */
-(LBFMDBMaker*(^)(NSString*tableName))Select;

/*
 *开启数据库操作
 *参数解释：
 *1.handler:数据库操作完毕给业务类的回执
 *注：开启操作的函数，会执行此次链式操作生成的所有sql语句。此函数也代表一次链式操作的终结，执行完毕后会清空除fmdbQueue的所有属性。
 */
-(void)fire:(void(^)(void))handler;
@end
