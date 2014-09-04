#import "AdColonyIOSDelegate.h"

@implementation AdColonyIOSDelegate

-(id)init
{
    [super init];
    observer_ = NULL;
    return self;
}

-(void)registerObserver:(CCAdColonyObserver *)observer
{
    observer_=observer;
}

-(void)onAdColonyV4VCReward:(BOOL)success currencyName:(NSString *)currencyName currencyAmount:(int)amount inZone:(NSString *)zoneID
{
    if (success) {
        NSLog(@"AdColony reward success, currency %@, amount %d, zone %@", currencyName, amount, zoneID);
        if (observer_){
            observer_->onReward(amount, [zoneID cStringUsingEncoding:NSUTF8StringEncoding]);
        }
    }else {
        NSLog(@"AdColony reward transaction failed\n");
    }
}
-(void)onAdColonyAdStartedInZone:(NSString *)zoneID
{
    NSLog(@"AdColony ad started in zone %@", zoneID);
    if (observer_){
        observer_->onAdStart([zoneID cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}
-(void)onAdColonyAdAttemptFinished:(BOOL)shown inZone:(NSString *)zoneID
{
    NSLog(@"AdColony ad finished, shown %d, zone %@", shown, zoneID);
    if (observer_){
        observer_->onAdFinish(shown, [zoneID cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}
@end