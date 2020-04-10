var AnimationsEffects;
var Brightness;
var CurrentAnimation;
var PowerState = false;
function CreateAnimationWindow()   {
    ClearElements();
    var main = document.getElementById("main");
    var fragment = document.createDocumentFragment();
    fragment.appendChild(CreateForm(
        CreateWrapper(
        CreateBackButton(),
        CreateImage("Animations")
        )));    
    fragment.appendChild(Separator());
    fragment.appendChild(    
        CreateWrapper(    
        CreateFormLeft(
            CreateButtonImageWithID("PowerOff","PowerStateButton()","PowerButton")),
        CreateFormRight(
            CreateImage("Brightness"),
            CreateProgressBar("Brightness","SetBrightness()")
        )));

    fragment.appendChild(Separator());
    fragment.appendChild(
        CreateForm(
        CreateWrapper(
            CreateButtonImage("previous","PreviousAnimation()"),
            CreateSelect("AnimationsList","ChangeAnimation()",null),
            CreateButtonImage("next","NextAnimation()")
        )));
    main.appendChild(fragment);
    LoadDataAnimations();
}
function ChangeAnimation()
{
    var div = document.getElementById("AnimationsList");
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/Animations/Animation?Animation=' + div.value, false);
    xhr.send();
}
function NextAnimation()
{
    var div = document.getElementById("AnimationsList");
    div.selectedIndex++;
    if(div.value == "")
    {
        div.selectedIndex = 0;
    }
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/Animations/Animation?Animation=' + div.value, false);
    xhr.send();
}
function PreviousAnimation()
{
    var div = document.getElementById("AnimationsList");
    div.selectedIndex--;
    
    if(div.value == "")
    {
        div.selectedIndex = AnimationsEffects.length - 1;
    }
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/Animations/Animation?Animation=' + div.value, false);
    xhr.send();
}
function LoadDataAnimations()
{
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (this.status == 200) {
            var data = JSON.parse(this.responseText);
            AnimationsEffects = data.AnimationsList;
            Brightness = data.Brightness / 256 * 100;
            CurrentAnimation = data.CurrentAnimation;
            var div = document.getElementById("Brightness");
            div.value = Brightness;

            div = document.getElementById("PowerButton");
            if(Brightness > 0)
            {                
                div.removeChild[0];
                div.appendChild(CreateButtonImageWithID("PowerOn","PowerStateButton()","PowerButton"));
                PowerState=true;
            }
            else
            {
                div.removeChild[0];
                div.appendChild(CreateButtonImageWithID("PowerOff","PowerStateButton()","PowerButton"));
                PowerState = false;
            }
                        
            div = document.getElementById("AnimationsList");
            div.removeChild(div.childNodes[0]);
            for(var i=0;i<AnimationsEffects.length;i++)
            {
                var option = document.createElement("option");
                option.text = AnimationsEffects[i];
                div.appendChild(option);
            } 
            for(var i=0;i<AnimationsEffects.length;i++)
            {
                if(CurrentAnimation == AnimationsEffects[i])
                {
                    div.selectedIndex = i;
                }
            }
        }
    };
    xhr.open('GET', '/Animations/Data', false);

    xhr.send();
}
function SetBrightness()
{
    var element = document.getElementById("Brightness");
    var value = element.value;
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '/Animations/Brightness?Brightness=' + value, false);

    xhr.send();
}
function PowerStateButton()
{
    PowerState = !PowerState;
    var res = "";
    if(PowerState)
        res="On";
    else
        res="Off";
    div = document.getElementById("PowerButton");
    //ClearChilds(div);
    if(PowerState)
    {                
        div.removeChild(div.firstChild);
        div.appendChild(CreateImage("PowerOn"));
    }
    else
    {
        div.removeChild(div.firstChild);
        div.appendChild(CreateImage("PowerOff"));
    }
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '/Animations/PowerState?'+ "PowerState" + '=' + res, false);

    xhr.send();
}