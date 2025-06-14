#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class Users;
class Pages;
class Facebook;
class Helper;
class Comment;
class Activity;
class Object;
class Date;
class Post;
class Memory;
class Helper
{
public:
        static int StringLength(const char *str)
        {
                int length = 0;
                for (int i = 0; str[i] != '\0'; i++)
                {
                        length++;
                }
                return length;
        }
        static int compareStr(char str1[], char str2[])
        {
                int check = 1;
                for (int i = 0; str1[i] != '\0'; i++)
                {
                        if (str1[i] != str2[i])
                        {
                                check = 0;
                                break;
                        }
                }
                return check;
        }
        static char *GetStringFromBuffer(const char *oldArr)
        {
                int strLen = StringLength(oldArr);
                char *str = 0;

                if (strLen > 0)
                {
                        str = new char[strLen + 1];
                        char *tempDest = str;

                        for (const char *tempSrc = oldArr; *tempSrc != '\0'; tempSrc++, tempDest++)

                        {
                                *tempDest = *tempSrc;
                        }
                        *tempDest = '\0';
                }
                return str;
        }
        static char *StringConcatenate(char *string1, const char *string2)
        {
                int i;
                int strArr1 = StringLength(string1);
                int strArr2 = StringLength(string2);
                int j = 0;
                char *temp = new char[strArr1 + strArr2 + 1];
                for (int index = 0; string1[index] != '\0'; index++)
                {
                        temp[index] = string1[index];
                }
                for (i = strArr1; i < strArr1 + strArr2; i++)
                {
                        temp[i] = string2[j];
                        j++;
                }
                temp[strArr1 + strArr2] = '\0';
                return temp;
        }
};
class Activity
{
        int activityType;
        char *value;

public:
        void readDataActivity(ifstream &fin)
        {
                char *temp = new char[100];
                fin >> activityType;
                fin.getline(temp, 100);
                value = Helper::GetStringFromBuffer(temp);
        }
        void PrintActivity()
        {
                if (activityType == 1)
                {
                        cout << " is feeling " << value << endl;
                }
                else if (activityType == 2)
                {
                        cout << " is thinking about " << value << endl;
                }
                else if (activityType == 3)
                {
                        cout << " is Making " << value << endl;
                }
                else if (activityType == 4)
                {
                        cout << " is celebrating " << value << endl;
                }
        }
        ~Activity()
        {
                if (value != 0)
                {
                        delete[] value;
                }
        }
};
class Object
{
        char *ID;

public:
        char *GetID()
        {
                return ID;
        }
        void SetID(char *id)
        {

                ID = Helper::GetStringFromBuffer(id);
        }
        virtual void AddPostToTimeline(Post *ptr)
        {
        }
        virtual void PrintName()
        {
        }
        virtual void searchPostByDate()
        {
        }
        virtual ~Object()
        {
                if (ID != 0)
                {
                        delete[] ID;
                }
        }
};
class Date
{
        int Day;
        int Month;
        int Year;
        static Date CurrentDate;

public:
        void readDatefromfile(ifstream &fin)
        {
                fin >> Day;
                fin >> Month;
                fin >> Year;
        }
        void PrintDate()
        {
                cout <<"\t"<< Day << " / " << Month << " / " << Year;
        }
        Date()
        {
                Day = CurrentDate.Day;
                Month = CurrentDate.Month;
                Year = CurrentDate.Year;
        }
        static void SetCurrentDate(int D, int M, int Y)
        {
                CurrentDate.Day = D;
                CurrentDate.Month = M;
                CurrentDate.Year = Y;
        }
        bool CompareDate()
        {
                if (Day == CurrentDate.Day || Day == CurrentDate.Day - 1 && Year == CurrentDate.Year && Month && Month == CurrentDate.Month)
                {
                        return true;
                }
                return false;
        }
        bool CompareDATE()
        {
                if ((Day == CurrentDate.Day && Month && Month == CurrentDate.Month) && Year < CurrentDate.Year)
                {
                        cout << endl<< endl<< CurrentDate.Year - Year << " Years Ago";
                        return true;
                }
                return false;
        }
        ~Date()
        {
                Day = 0;
                Month = 0;
                Year = 0;
        }
};
class Comment
{
        char *CommentID;
        char *CommentText;
        Object *CommentsBy;

public:
        static int totalComments;
        Comment()
        {
                totalComments++;
        }
        void SetCommentBy(Object *value)
        {
                CommentsBy = value;
        }
        void AddComment(Object *obj, const char *txt, Post *post);
        void SetCommenttext(const char *value)
        {
                CommentText = Helper::GetStringFromBuffer(value);
        }
        void ViewComment()
        {
                CommentsBy->PrintName();
                cout << " wrote: ''" << CommentText << "''\n";
        }
        ~Comment()
        {
                if (CommentID != 0)
                {
                        delete[] CommentID;
                }
                if (CommentText != 0)
                {
                        delete[] CommentText;
                }
        }
};
class Post
{
        int postType;
        char *postID;
        Date PostShareDate;
        char *description;
        int NoOfLikes;
        int NoOfComments;
        Object *SharedBy;
        Activity *activity;
        Object **LikedBy;
        Comment **comments;

public:
        void printMemory()
        {
                SharedBy->PrintName();
                if (postType == 2)
                {
                        activity->PrintActivity();
                }
                else
                {
                        cout << " Shared ";
                }
                cout << endl << " \"" << description << "  \"" << endl;
                cout << endl;
                for (int i = 0; i < NoOfComments; i++)
                {
                        comments[i]->ViewComment();
                        cout << endl;
                }
        }
        Object *GetSharedBy()
        {
                return SharedBy;
        }
        Post();
        char *getDiscription()
        {
                return description;
        }
        ~Post()
        {

                if (postID != 0)
                {
                        delete[] postID;
                }
                if (description != 0)
                {
                        delete[] description;
                }
                if (comments != 0)
                {
                        for (int i = 0; i < NoOfComments; i++)
                        {
                                if (comments[i] != 0)
                                {
                                        delete comments[i];
                                }
                        }
                }
                comments = 0;
        }
        void AddComment(Users *Ptr, const char *TextArray);
        Post *seeYourMemory();
        void postBy(Object *ptr)
        {
                *&SharedBy = *&ptr;
        }
        void LikeBy(Object *ptr, int i)
        {
                if (!i)
                {
                        LikedBy = new Object *[10];
                }
                *&LikedBy[i] = *&ptr;
                NoOfLikes++;
        }
        void Commentby(Comment *ptr)
        {
                if (!NoOfComments)
                {

                        comments = new Comment *[10];
                }
                if (NoOfComments < 10)
                {
                        comments[NoOfComments] = ptr;
                        NoOfComments++;
                }
        }
        Post(const char *text, Object *ptr)
        {
                description = Helper::GetStringFromBuffer(text);
                SharedBy = ptr;
        }
        void readDataPosts(ifstream &fin)
        {
                char temp[100];
                fin >> postType;
                fin >> temp;
                postID = Helper::GetStringFromBuffer(temp);
                PostShareDate.readDatefromfile(fin);
                fin >> temp;
                fin.getline(temp, 100);
                description = Helper::GetStringFromBuffer(temp);
                if (postType == 2)
                {
                        activity = new Activity;
                        activity->readDataActivity(fin);
                }
        }
        int GetNumOfLikes()
        {
                return NoOfLikes;
        }
        virtual void PrintPost(bool flag1, bool flag2)
        {
                cout << "---";
                cout << endl;
                SharedBy->PrintName();
                if (postType == 2)
                {
                        activity->PrintActivity();
                }
                else
                {
                        cout << " Shared ";
                }
                cout << endl<< " \"" << description << "  \"" << endl;
                if (flag1 == true)
                {
                        PostShareDate.PrintDate();
                        cout << endl;
                }
                if (flag2 == true)
                {
                        for (int i = 0; i < NoOfComments; i++)
                        {
                                comments[i]->ViewComment();
                                cout << endl;
                        }
                }
        }
        char *GetPostID()
        {
                return postID;
        }
        Date GetPostDate()
        {
                return PostShareDate;
        }
};
class Pages : public Object
{
private:
        char *Title;
        Post **TimeLine;
        int NoOfTimeLinePost;

public:
        Pages()
        {
                Title = 0;
                NoOfTimeLinePost = 0;
        }
        void readDataPages(ifstream &fin)
        {
                char temp[50];
                fin >> temp;
                SetID(temp);
                fin.getline(temp, 50);
                Title = Helper::GetStringFromBuffer(temp);
                cout << GetID() << " ";
                cout << Title;
                cout << endl;
        }
        void AddPostToTimeline(Post *ptr)
        {
                if (!NoOfTimeLinePost)
                {
                        TimeLine = new Post *[10];
                }
                *&TimeLine[NoOfTimeLinePost] = *&ptr;
                NoOfTimeLinePost++;
        }
        void PrintName()
        {
                cout << Title << " ";
        }
        void PrintPages()
        {
                cout << GetID() << "  " << Title << "\t";
        }
        void searchPostByDate()
        {
                for (int i = 0; i < NoOfTimeLinePost; i++)
                {
                        Date DatePost = TimeLine[i]->GetPostDate();
                        bool CHECK = DatePost.CompareDate();
                        if (CHECK == true)
                        {
                                TimeLine[i]->PrintPost(false, false);
                        }
                }
        }
        ~Pages()
        {
                if (Title != 0)
                {
                        delete[] Title;
                }
                if (TimeLine != 0)
                {
                        for (int i = 0; i < NoOfTimeLinePost; i++)
                        {
                                if (TimeLine[i] != 0)
                                {
                                        delete TimeLine[i];
                                }
                        }
                }
                TimeLine = 0;
        }
};
class Users : public Object
{
private:
        char *FName;
        char *LName;
        Pages **LikedPages;
        Users **FriendList;
        Post **TimeLine;
        int NoOfTimeLinePost;
        int PageCount;
        int FriendCount;

public:
        void readDataUsers(ifstream &fin)
        {
                char temp[50];
                fin >> temp;
                SetID(temp);
                fin.getline(temp, 50, ' ');
                FName = Helper::GetStringFromBuffer(temp);
                fin.getline(temp, 50, '\t');
                LName = Helper::GetStringFromBuffer(temp);
                cout << GetID() << "  ";
                cout << FName << " ";
                cout << LName << "\t";
        }
        void LikedPagesSS(Pages *ptr, int i)
        {
                if (!i)
                {
                        LikedPages = new Pages *[10];
                }
                *&LikedPages[i] = *&ptr;
                LikedPages[i]->PrintPages();
                PageCount++;
        }
        void Addfriend(Users *ptr, int i)
        {
                if (!i)
                {
                        FriendList = new Users *[10];
                }
                *&FriendList[i] = *&ptr;
                FriendCount++;
        }
        Post *CheckTimeLine()
        {
                bool check = false;
                Post *MemoryPost = new Post;
                for (int i = 0; i < NoOfTimeLinePost; i++)
                {
                        MemoryPost = TimeLine[i]->seeYourMemory();
                        if (MemoryPost)
                        {
                                return MemoryPost;
                        }
                }
                return 0;
        }
        void AddPostToTimeline(Post *ptr)
        {
                if (!NoOfTimeLinePost)
                {
                        TimeLine = new Post *[10];
                }
                *&TimeLine[NoOfTimeLinePost] = *&ptr;
                NoOfTimeLinePost++;
        }
        void PrintFriends()
        {
                cout << GetID() << " " << FName << " " << LName << endl;
        }
        void PrintName()
        {
                cout << FName << "  " << LName << " ";
        }
        void ViewFriendList()
        {
                cout << this->FName << " " << this->LName;
                cout << "\nFriend List : " << endl;
                for (int i = 0; i < FriendCount; i++)
                {
                        FriendList[i]->PrintFriends();
                }
        }
        void ViewLikedPages()
        {
                Pages *temp = 0;
                cout << "\nPages List : " << endl;
                for (int i = 0; i < PageCount; i++)
                {
                        LikedPages[i]->PrintPages();
                        cout << endl;
                }
        }
        void searchPostByDate()
        {
                for (int i = 0; i < NoOfTimeLinePost; i++)
                {
                        Date DatePost = TimeLine[i]->GetPostDate();
                        bool CHECK = DatePost.CompareDate();
                        if (CHECK == true)
                        {
                                TimeLine[i]->PrintPost(true, true);
                        }
                }
        }
        void ViewTimeLine()
        {
                cout << this->FName << " " << this->LName;
                cout << "-Timeline " << endl;
                for (int i = 0; i < NoOfTimeLinePost; i++)
                {
                        TimeLine[i]->PrintPost(true, true);
                        cout << endl;
                }
        }
        void ViewHomePage()
        {
                cout << endl;
                this->PrintName();
                cout << "--Homepage";
                for (int i = 0; i < FriendCount; i++)
                {
                        FriendList[i]->searchPostByDate();
                }
                for (int i = 0; i < PageCount; i++)
                {
                        LikedPages[i]->searchPostByDate();
                }
        }
        Users()
        {
                FName = 0;
                LName = 0;
                LikedPages = 0;
                FriendList = 0;
                PageCount = 0;
                FriendCount = 0;
                NoOfTimeLinePost = 0;
        }
        ~Users()
        {
                delete[] FName;
                delete[] LName;
                delete[] LikedPages;
                if (TimeLine != 0)
                {
                        for (int i = 0; i < NoOfTimeLinePost; i++)
                        {
                                if (TimeLine[i] != 0)
                                {
                                        delete TimeLine[i];
                                }
                        }
                }
                TimeLine = 0;
                FName = 0;
                LName = 0;
        }
};
class Memory : public Post
{
private:
        Post *OrignalPost;

public:
        Memory(Post *&oldPost, const char *text, Object *userPtr) : Post(text, userPtr)
        {
                OrignalPost = oldPost;
        }
        void PrintPost(bool flag1, bool flag2)
        {
                cout << "---";
                cout << endl;
                printMemory();
                OrignalPost->PrintPost(false, false);
                cout << endl;
        }
};
void Post::AddComment(Users *Ptr, const char *TextArray)
{
}
class Facebook
{
private:
        Pages **pages;
        Users **user;
        Post **posts;
        Comment *commentPtr;

public:
        static int TotalPages;
        static int TotalUsers;
        static int TotalPosts;
        static int TotalComments;
        static int GetTotalPosts()
        {
                return TotalPosts;
        }
        void loadPagesFromFile()
        {
                ifstream fin;
                fin.open("SocialNetworkPages.txt");
                if (fin.is_open())
                {
                        int j = 0;
                        fin >> TotalPages;
                        pages = new Pages *[TotalPages];
                        while (!fin.eof())
                        {
                                for (int i = 0; i < TotalPages; i++)
                                {
                                        pages[j] = new Pages;
                                        pages[i]->readDataPages(fin);
                                        j++;
                                }
                        }
                }
                else
                {
                        cout << "\nFile is not opened!";
                }
                fin.close();
        }
        Pages *searchPageID(char *temp)
        {
                char *IDptr;
                for (int i = 0; i < TotalPages; i++)
                {
                        IDptr = pages[i]->GetID();
                        int check = Helper::compareStr(temp, IDptr);
                        if (check == 1)
                        {
                                return &*pages[i];
                        }
                }
                return 0;
        }
        Users *searchUserID(char *temp)
        {
                char *IDptr;
                for (int i = 0; i < TotalUsers; i++)
                {
                        IDptr = user[i]->GetID();
                        int check = Helper::compareStr(temp, IDptr);
                        if (check == 1)
                        {
                                return &*user[i];
                        }
                }
                return 0;
        }
        Object *searchObjectByID(char *temp)
        {
                Object *temp1 = 0;
                if (temp[0] == 'u')
                {
                        temp1 = searchUserID(temp);
                }
                else if (temp[0] == 'p')
                {
                        temp1 = searchPageID(temp);
                }
                return temp1;
        }
        Post *searchPostByID(char *temp)
        {
                for (int i = 0; i < TotalPosts; i++)
                {
                        char *PostID = posts[i]->GetPostID();
                        int CHECK = Helper::compareStr(PostID, temp);
                        if (CHECK == 1)
                        {
                                return &*posts[i];
                        }
                }
                return 0;
        }
        Users *SetCurrentUser(char *temp)
        {
                cout << "User : \n";
                Users *CurrentUser = searchUserID(temp);
                return CurrentUser;
        }
        void loadUsersFromFile()
        {
                char ***tempFriendID = NULL;
                char *temp = new char[10];
                ifstream fin;
                fin.open("SocialNetworkUsers.txt");
                if (fin.is_open())
                {
                        int i, j;
                        fin >> TotalUsers;
                        tempFriendID = new char **[TotalUsers];
                        user = new Users *[TotalUsers];
                        while (!fin.eof())
                        {
                                for (i = 0; i < TotalUsers; i++)
                                {
                                        user[i] = new Users;
                                        user[i]->readDataUsers(fin);
                                        for (j = 0; temp[0] != '-' || temp[1] != '1'; j++)
                                        {
                                                fin >> temp;
                                                if (!j)
                                                {
                                                        tempFriendID[i] = new char *[10];
                                                }
                                                if (temp[0] != '-' || temp[1] != '1')
                                                {
                                                        tempFriendID[i][j] = Helper::GetStringFromBuffer(temp);
                                                        cout << tempFriendID[i][j] << "\t";
                                                }
                                        }
                                        tempFriendID[i][j - 1] = NULL;

                                        temp[0] = 0, temp[1] = 0;
                                        for (int j = 0; temp[0] != '-' || temp[1] != '1'; j++)
                                        {
                                                fin >> temp;
                                                if (temp[0] != '-' || temp[1] != '1')
                                                {
                                                        Pages *likePages = searchPageID(temp);
                                                        user[i]->LikedPagesSS(likePages, j);
                                                }
                                        }
                                        cout << endl;
                                        temp[0] = 0, temp[1] = 0;
                                }
                        }
                }
                else
                {
                        cout << "\nFile is not opened!";
                }
                fin.close();
                Users *Friends;
                for (int j = 0; j < TotalUsers; j++)
                {
                        for (int i = 0; tempFriendID[j][i] != NULL; i++)
                        {
                                Friends = searchUserID(tempFriendID[j][i]);
                                user[j]->Addfriend(Friends, i);
                        }
                }
        }
        void loadPostsFromFile()
        {
                int i = 0;
                ifstream fin;
                char *temp = new char[10];
                fin.open("Post.txt");
                if (fin.is_open())
                {
                        fin >> TotalPosts;
                        posts = new Post *[TotalPosts];
                        while (!fin.eof())
                        {
                                posts[i] = new Post;
                                posts[i]->readDataPosts(fin);
                                fin >> temp;
                                Object *postedBy = searchObjectByID(temp);
                                posts[i]->postBy(postedBy);
                                postedBy->AddPostToTimeline(posts[i]);
                                for (int j = 0; temp[0] != '-' || temp[1] != '1'; j++)
                                {
                                        fin >> temp;
                                        if (temp[0] != '-' || temp[1] != '1')
                                        {
                                                Object *Ptr = searchObjectByID(temp);
                                                posts[i]->LikeBy(Ptr, j);
                                        }
                                }
                                i++;
                        }
                }
                else
                {
                        cout << "\nFile is not opened!";
                }
                fin.close();
        }
        void loadCommentsFromFile()
        {
                char *ID = 0;
                char *CommentedBy = 0;
                char *Text = 0;
                fstream fin;
                char *temp = new char[100];
                fin.open("Comments.txt");
                if (fin.is_open())
                {
                        fin >> TotalComments;
                        for (int i = 0; i < TotalComments; i++)
                        {
                                commentPtr = new Comment;
                                fin >> temp;
                                ID = Helper::GetStringFromBuffer(temp);
                                fin >> temp;
                                Post *postPtr = searchPostByID(temp);
                                postPtr->Commentby(commentPtr);
                                fin >> temp;
                                CommentedBy = Helper::GetStringFromBuffer(temp);
                                Object *Commentby = searchObjectByID(CommentedBy);
                                commentPtr->SetCommentBy(Commentby);
                                fin.getline(temp, 100);
                                Text = Helper::GetStringFromBuffer(temp);
                                commentPtr->SetCommenttext(Text);
                        }
                }
                else
                {
                        cout << "\nFile is not opened!";
                }
                fin.close();
        }
        void Run()
        {
                char *temp = new char[10];
                char temp1[] = "u7";
                Users *CurrentUser = SetCurrentUser(temp1);
                if (CurrentUser)
                {
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "----------------------------------------------------------VIEW FRIENDLIST!!!!!--------------------------------------------------------------" << endl;
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        CurrentUser->ViewFriendList();
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "----------------------------------------------------------VIEW LIKEDPAGES!!!!!--------------------------------------------------------------" << endl;
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        CurrentUser->ViewLikedPages();
                        temp = Helper::GetStringFromBuffer("post5");
                        Post *Ptr = searchPostByID(temp);
                        int j = Ptr->GetNumOfLikes();
                        Ptr->LikeBy(CurrentUser, j);
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "----------------------------------------------------------VIEW TIMELINE!!!!!--------------------------------------------------------------" << endl;
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        CurrentUser->ViewTimeLine();
                        Comment *ptr = new Comment;
                        ptr->AddComment(CurrentUser, "You look like pakora chai sath kha jaunga", Ptr);
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "----------------------------------------------------VIEW POST AFTER ADD COMMENT!!!!!--------------------------------------------------" << endl;
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        Ptr->PrintPost(false, true);
                        Date::SetCurrentDate(15, 11, 2017);
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "------------------------------------------------------VIEW HOMEPAGE!!!!!!!--------------------------------------------------------------------------" << endl;
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        CurrentUser->ViewHomePage();
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "----------------------------------------------------------VIEW SHARED MEMORYYYY!!!!!--------------------------------------------------------------" << endl;
                        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        Post *memoryPtr = CurrentUser->CheckTimeLine();
                        if (memoryPtr)
                        {
                                Memory *memo = new Memory(memoryPtr, "GOOD OLD MEMORIES", CurrentUser);
                                memo->PrintPost(false, false);
                        }
                        else
                        {
                                cout << "\nOrignal post doesnt exists";
                        }
                }
                else
                {
                        cout << "\nUser doesnt exists";
                }
        }
        void load()
        {
                loadPagesFromFile();
                loadUsersFromFile();
                loadPostsFromFile();
                loadCommentsFromFile();
        }
        ~Facebook()
        {
                if (pages != 0)
                {
                        for (int i = 0; i < TotalPages; i++)
                        {
                                if (pages[i] != 0)
                                {
                                        delete pages[i];
                                }
                        }
                }
                pages = 0;
                if (user != 0)
                {
                        for (int i = 0; i < TotalUsers; i++)
                        {
                                delete user[i];
                        }
                }
                user = 0;
                delete[] posts;
        }
};
void Comment::AddComment(Object *obj, const char *txt, Post *post)
{
        CommentText = Helper::GetStringFromBuffer(txt);
        SetCommentBy(obj);
        post->Commentby(this);
        char temp2[] = "c";
        string temp = to_string(totalComments);
        const char *temp1 = temp.c_str();
        CommentID = Helper::StringConcatenate(temp2, temp1);
}
Post *Post ::seeYourMemory()
{
        bool check = false;
        check = PostShareDate.CompareDATE();
        if (check == true)
        {
                this->PrintPost(false, false);
                return this;
        }
        return 0;
}
Post::Post()
{
        NoOfComments = 0;
        NoOfLikes = 0;
        postType = 0;
        description = 0;
        int TPost = Facebook::GetTotalPosts();
        char temp2[] = "post";
        string temp = to_string(TPost);
        const char *temp1 = temp.c_str();
        postID = Helper::StringConcatenate(temp2, temp1);
}
int Facebook::TotalPages = 0;
int Facebook::TotalUsers = 0;
int Facebook::TotalPosts = 0;
int Facebook::TotalComments = 0;
Date Date ::CurrentDate;
int Comment::totalComments = 0;
int main()
{
        Facebook fb;
        fb.load();
        fb.Run();
        int t;
        cin >> t;
        cout << t;
}


